#Eight 0.1s 1.5 1.2
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.uic import loadUi
from PyQt5.QtCore import QTimer, pyqtSignal, QObject, QThread
import threading
import socket
import sys
import pyqtgraph as pg
import numpy as np
import ctypes
from ctypes import Structure, c_double, POINTER
import csv

class ExtU(Structure):
    _fields_ = [
        ("Q", c_double * 3),
        ("Q_dot", c_double * 3),
    ]
    
class ExtY(Structure):
    _fields_ = [
        ("w1", c_double),
        ("w2", c_double),
        ("w3", c_double),
        ("w4", c_double),
        ("Tp", c_double * 4),
    ]
           
class ReceiveThread(QThread):
    data_received = pyqtSignal(str)

    def __init__(self, socket):
        super().__init__()
        self.socket = socket
        self.running = True

    def run(self):
        while self.running:
            try:
                data = self.socket.recv(1024)
                if data:
                    received_text = data.decode("utf-8")
                    self.data_received.emit(received_text)
            except OSError as e:
                print("Error receiving data:", e)
                self.stop()

    def stop(self):
        self.running = False
        self.socket.close()
        self.wait()
               
class MainWindow(QMainWindow):
    
    def __init__(self):
        super().__init__()
        loadUi("D:\THANH\HK232\DoAnTN\python\GUI2.ui", self)
        
        self.eight = ctypes.CDLL(r'D:\THANH\HK232\DoAnTN\VS\eight\last8\x64\Debug\last8.dll')
        self.eight.last8_initialize.restype = None
        self.eight.last8_initialize.argtypes = []
        self.eight.last8_step.restype = None
        self.eight.last8_step.argtypes = []
        self.eight.get_rtU.restype = POINTER(ExtU)
        self.eight.get_rtU.argtypes = []
        self.eight.get_rtY.restype = POINTER(ExtY)
        self.eight.get_rtY.argtypes = []

        self.start_time = 0
        
        self.eight.last8_initialize()
        self.rtU = self.eight.get_rtU().contents
        self.rtY = self.eight.get_rtY().contents        
                  
        self.timer1 = QTimer()
        self.timer1.timeout.connect(self.timeout1) 
        self.timer2 = QTimer()
        self.timer2.timeout.connect(self.timeout2) 
       
        self.connected = False
        self.esp_socket = None
        self.receive_thread = None
        
        self.setup_signals()
        
        self.float_values = [0.0] * 8
        
        #do thi
        self.x = np.array([])
        self.y = np.array([]) #reference         
        self.plotWidget = pg.PlotWidget()
        posWidget = self.findChild(QWidget,'plotPos')
        layout1 = QVBoxLayout(posWidget)
        layout1.addWidget(self.plotWidget)
        self.plotWidget.setBackground('w')
        self.plotWidget.setTitle("Position")
        self.plotWidget.setLabel('left', "y", "m")
        self.plotWidget.setLabel('bottom', "x", "m")
        self.plotWidget.setXRange(0, 3, padding=0)
        self.plotWidget.setYRange(0, 3, padding=0)
        
        self.plot_curve = self.plotWidget.plot(pen=pg.mkPen(color=(255,0,0),width=2))
        self.x_data = np.array([])
        self.y_data = np.array([])
        self.plot_curve_2 = self.plotWidget.plot(pen=pg.mkPen(color=(0,255,0),width=2))
        self.x_data_2 = np.array([])
        self.y_data_2 = np.array([])        
        
        self.pos_e_Widget = self.findChild(QWidget,'plot_e')
        layout2 = QVBoxLayout(self.pos_e_Widget)               
        self.plot_x = pg.PlotWidget()
        self.plot_y = pg.PlotWidget()
        self.plot_theta = pg.PlotWidget()
        self.configure_plot(self.plot_x, "Error X", "e_x", "m", "t", "s")
        self.configure_plot(self.plot_y, "Error Y", "e_y", "m", "t", "s")
        self.configure_plot(self.plot_theta, "Error Theta", "e_theta", "rad", "t", "s")
        layout2.addWidget(self.plot_x)
        layout2.addWidget(self.plot_y)
        layout2.addWidget(self.plot_theta)
        
        self.pos_e_2_Widget = self.findChild(QWidget,'plot_e_2')
        layout3 = QVBoxLayout(self.pos_e_2_Widget)         
        self.plot_x_2 = pg.PlotWidget()
        self.plot_y_2 = pg.PlotWidget()
        self.plot_theta_2 = pg.PlotWidget()
        self.configure_plot(self.plot_x_2, "Error X", "e_x", "m", "t", "s")
        self.configure_plot(self.plot_y_2, "Error Y", "e_y", "m", "t", "s")
        self.configure_plot(self.plot_theta_2, "Error Theta", "e_theta", "rad", "t", "s")
        layout3.addWidget(self.plot_x_2)
        layout3.addWidget(self.plot_y_2)
        layout3.addWidget(self.plot_theta_2) 
        
        self.error_x_data = np.array([])
        self.error_y_data = np.array([])
        self.error_theta_data = np.array([])
        self.time = np.array([])
        
        self.plot_x_curve = self.plot_x.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_y_curve = self.plot_y.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_theta_curve = self.plot_theta.plot(pen=pg.mkPen(color='r', width=2)) 
        
        self.error_x_data_2 = np.array([])
        self.error_y_data_2 = np.array([])
        self.error_theta_data_2 = np.array([])
        
        self.plot_x_2_curve = self.plot_x_2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_y_2_curve = self.plot_y_2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_theta_2_curve = self.plot_theta_2.plot(pen=pg.mkPen(color='r', width=2)) 
        
        t = np.linspace(0, 15, 1000)
        self.ref_x = 0.5*np.sin(2*np.pi/15*t) + 1.5
        self.ref_y = 0.5*np.sin(4*np.pi/15*t) + 1.2
        self.ref_theta = 0
        
        self.pos_T_Widget = self.findChild(QWidget,'plot_T')
        layout4 = QVBoxLayout(self.pos_T_Widget)               
        self.plot_T1 = pg.PlotWidget()
        self.plot_T2 = pg.PlotWidget()
        self.plot_T3 = pg.PlotWidget()
        self.plot_T4 = pg.PlotWidget()
        self.configure_plot(self.plot_T1, "T1", "u1", "Nm", "t", "s")
        self.configure_plot(self.plot_T2, "T2", "u2", "Nm", "t", "s")
        self.configure_plot(self.plot_T3, "T3", "u3", "Nm", "t", "s")
        self.configure_plot(self.plot_T4, "T4", "u4", "Nm", "t", "s")
        layout4.addWidget(self.plot_T1)
        layout4.addWidget(self.plot_T2)
        layout4.addWidget(self.plot_T3)
        layout4.addWidget(self.plot_T4)
        
        self.T1_data = np.array([])
        self.T2_data = np.array([])
        self.T3_data = np.array([])
        self.T4_data = np.array([])
        
        self.plot_T1_curve = self.plot_T1.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T2_curve = self.plot_T2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T3_curve = self.plot_T3.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T4_curve = self.plot_T4.plot(pen=pg.mkPen(color='r', width=2))
        
        self.pos_T_2_Widget = self.findChild(QWidget,'plot_T_2')
        layout5 = QVBoxLayout(self.pos_T_2_Widget)               
        self.plot_T1_2 = pg.PlotWidget()
        self.plot_T2_2 = pg.PlotWidget()
        self.plot_T3_2 = pg.PlotWidget()
        self.plot_T4_2 = pg.PlotWidget()
        self.configure_plot(self.plot_T1_2, "T1", "u1", "Nm", "t", "s")
        self.configure_plot(self.plot_T2_2, "T2", "u2", "Nm", "t", "s")
        self.configure_plot(self.plot_T3_2, "T3", "u3", "Nm", "t", "s")
        self.configure_plot(self.plot_T4_2, "T4", "u4", "Nm", "t", "s")
        layout5.addWidget(self.plot_T1_2)
        layout5.addWidget(self.plot_T2_2)
        layout5.addWidget(self.plot_T3_2)
        layout5.addWidget(self.plot_T4_2)
        
        self.T1_2_data = np.array([])
        self.T2_2_data = np.array([])
        self.T3_2_data = np.array([])
        self.T4_2_data = np.array([])
        
        self.plot_T1_2_curve = self.plot_T1_2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T2_2_curve = self.plot_T2_2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T3_2_curve = self.plot_T3_2.plot(pen=pg.mkPen(color='r', width=2))
        self.plot_T4_2_curve = self.plot_T4_2.plot(pen=pg.mkPen(color='r', width=2))
        
        #error
        self.filename = 'D:\THANH\HK232\DoAnTN\MATLAB\error\error5.csv'
        with open(self.filename, mode='w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Time", "Error_XP", "Error_YP", "Error_ThetaP", "Error_XV", "Error_YV", "Error_ThetaV"])
                      
        self.filename1 = 'D:\THANH\HK232\DoAnTN\MATLAB\error\pos3.csv'
        with open(self.filename1, mode='w', newline='') as file1:
            writer1 = csv.writer(file1)
            writer1.writerow(["Time", "X", "Y", "Theta"])
                      
    def configure_plot(self, plot_widget, title, ylabel, yunit, xlabel, xunit):
        plot_widget.setBackground('w')
        plot_widget.setTitle(title)
        plot_widget.setLabel('left', ylabel, yunit)
        plot_widget.setLabel('bottom', xlabel, xunit)
        plot_widget.setXRange(0, 100, padding=0)
        plot_widget.setYRange(-5, 5, padding=0)
        
    def setup_signals(self):                          
        self.forw_button_1.clicked.connect(self.move_forward_1)
        self.back_button_1.clicked.connect(self.move_backward_1)
        self.left_button_1.clicked.connect(self.turn_left_1)
        self.rigt_button_1.clicked.connect(self.turn_right_1)
        self.stop_button_1.clicked.connect(self.stop_robot_1)
        self.fl_button_1.clicked.connect(self.fl_1)
        self.fr_button_1.clicked.connect(self.fr_1)
        self.bl_button_1.clicked.connect(self.bl_1)
        self.br_button_1.clicked.connect(self.br_1)
        self.rotate_button_1.clicked.connect(self.rotate_1)
        self.rotate_button_2.clicked.connect(self.rotate_2)
        self.connect_button.clicked.connect(self.connect_to_esp)
        self.disconnect_button.clicked.connect(self.disconnect_from_esp)
        self.send_button.clicked.connect(self.send_command)
        self.run_button.clicked.connect(self.run_timer)
        self.stop_button_2.clicked.connect(self.stop_timer)
        self.clear_button.clicked.connect(self.clear_plot)
        #self.read_button.clicked.connect(self.receive_data)     
                       
    def timeout1(self):
        self.get_gps()
        #self.update_plot_2()
        #self.run_trajectory()
        #pass
                 
    def timeout2(self):
        #self.get_gps()
        self.run_trajectory()
        #self.test_1()
        #self.update_plot_2()    
        
    def update_plot_2(self):
        new_x = self.float_values[4]
        new_y = self.float_values[5]
        self.x_data_2 = np.append(self.x_data_2, new_x)
        self.y_data_2 = np.append(self.y_data_2, new_y)
        self.plot_curve_2.setData(self.x_data_2, self.y_data_2) 
           
    def update_error_plots(self, xp, yp, thetap, T1, T2, T3, T4):
        error_xp = self.closest_point_x_2 - xp
        error_yp = self.closest_point_y_2 - yp
        error_thetap = self.ref_theta - thetap
        
        self.start_time += 0.1
        
        self.error_x_data = np.append(self.error_x_data, error_xp)
        self.error_y_data = np.append(self.error_y_data, error_yp)
        self.error_theta_data = np.append(self.error_theta_data, error_thetap)
        
        self.T1_data = np.append(self.T1_data, T1)
        self.T2_data = np.append(self.T2_data, T2)
        self.T3_data = np.append(self.T3_data, T3)
        self.T4_data = np.append(self.T4_data, T4)
        
        self.time = np.append(self.time, self.start_time)
        
        self.plot_x_curve.setData(self.time, self.error_x_data)
        self.plot_y_curve.setData(self.time, self.error_y_data)
        self.plot_theta_curve.setData(self.time, self.error_theta_data)
             
        self.plot_T1_curve.setData(self.time, self.T1_data)
        self.plot_T2_curve.setData(self.time, self.T2_data)
        self.plot_T3_curve.setData(self.time, self.T3_data)
        self.plot_T4_curve.setData(self.time, self.T4_data)
        
        with open(self.filename, mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([self.start_time, error_xp, error_yp, error_thetap])

        with open(self.filename1, mode='a', newline='') as file1:
            writer1 = csv.writer(file1)
            writer1.writerow([self.start_time, self.float_values[4], self.float_values[5], self.float_values[6]])
               
    def clear_plot(self):   
        self.x_data_2 = np.array([])
        self.y_data_2 = np.array([])
        self.plot_curve_2.setData(self.x_data_2, self.y_data_2)
        
        self.plotWidget.removeItem(self.ref_curve)                   
        
        self.error_x_data = np.array([])
        self.error_y_data = np.array([])
        self.error_theta_data = np.array([])
        self.T1_data = np.array([])
        self.T2_data = np.array([])
        self.T3_data = np.array([])
        self.T4_data = np.array([])
        self.time = np.array([])
        
        self.plot_x_curve.setData(self.time, self.error_x_data)
        self.plot_y_curve.setData(self.time, self.error_y_data)
        self.plot_theta_curve.setData(self.time, self.error_theta_data)
        self.plot_T1_curve.setData(self.time, self.T1_data)
        self.plot_T2_curve.setData(self.time, self.T2_data)
        self.plot_T3_curve.setData(self.time, self.T3_data)
        self.plot_T4_curve.setData(self.time, self.T4_data)
        
    def connect_to_esp(self):
        esp_ip = '192.168.4.1'
        esp_port = 10020

        try:
            self.esp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.esp_socket.connect((esp_ip, esp_port))
            self.connected = True
            
            if self.receive_thread is None or not self.receive_thread.isRunning():
                self.receive_thread = ReceiveThread(self.esp_socket)
                self.receive_thread.data_received.connect(self.handle_received_data)
                self.receive_thread.start()
                
            #self.timer1.start(int(robot.getBasicTimeStep()))
            #self.timer1.start(100)
            #self.start_time = self.robot.getTime()
            print("Connected to ESP32")
        except Exception as e:
            print("Error connecting to ESP32:", e)
            
    def disconnect_from_esp(self):
        if self.connected and self.esp_socket:
            try:
                self.esp_socket.shutdown(socket.SHUT_RDWR)
                self.esp_socket.close()
                self.connected = False
                print("Disconnected from ESP32")
                if self.receive_thread and self.receive_thread.isRunning():
                    self.receive_thread.stop()
            except Exception as e:
                print("Error disconnecting from ESP32:", e)

    def send_command(self):
        if self.connected:
            try:
                command = self.textSend.toPlainText()
                self.esp_socket.send(command.encode("utf-8"))
                print("Sent command:", command)
            except Exception as e:
                print("Error sending command:", e)
                
    def handle_received_data(self, received_text):
        #print("Received:", received_text)
        try:
            received_text = received_text.strip()  
            self.textRead.setText(received_text)
            if received_text.startswith('E='):  
                en_values = received_text[2:].split(';')  
                if len(en_values) == 8: 
                    self.text_w1.setText(en_values[0])
                    self.text_w2.setText(en_values[1])
                    self.text_w3.setText(en_values[2])
                    self.text_w4.setText(en_values[3])
                    self.text_xp.setText(en_values[4])
                    self.text_yp.setText(en_values[5])
                    self.text_thetap.setText(en_values[6])
                    self.text_omega_2.setText(en_values[7])
            
                    self.float_values = [float(value) for value in en_values]
                    r = 0.097/2
            
                    if len(self.float_values) == 8: 
                        vx = round((r/4)*(self.float_values[0] + self.float_values[1] + self.float_values[2] + self.float_values[3])*2*np.pi/60,2)
                        vy = round((r/4)*(-self.float_values[0] + self.float_values[1] - self.float_values[2] + self.float_values[3])*2*np.pi/60,2)
            
                        self.text_vx_2.setText(str(vx))
                        self.text_vy_2.setText(str(vy))  
                                
                else:
                    print("Error: Invalid number of values received")
            else:
                print("Error: Invalid data format")
        except Exception as e:
            print("Error:", e)
                                                          
    def move_forward_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("f\r\n".encode("utf-8"))
    
    def move_backward_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("b\r\n".encode("utf-8"))
    
    def turn_left_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("l\r\n".encode("utf-8"))
    
    def turn_right_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("r\r\n".encode("utf-8"))
    
    def stop_robot_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("s\r\n".encode("utf-8"))
            
    def fl_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("a\r\n".encode("utf-8"))
            
    def fr_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("c\r\n".encode("utf-8"))

    def bl_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("d\r\n".encode("utf-8"))
            
    def br_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("e\r\n".encode("utf-8"))
                   
    def rotate_1(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("g\r\n".encode("utf-8"))  
            
    def rotate_2(self):
        if self.radio_button_1.isChecked():
            self.esp_socket.send("h\r\n".encode("utf-8"))
            
    def run_timer(self):
        if self.radio_button_2.isChecked():
            #self.timer2.start(int(robot.getBasicTimeStep()))
            self.timer2.start(80)
            self.ref_curve = self.plotWidget.plot(self.ref_x,self.ref_y,pen=pg.mkPen(color=(0,0,255),width=2))                    
            
    def stop_timer(self):
        self.timer2.stop()
        self.esp_socket.send("s\r\n".encode("utf-8"))
            
    def run_trajectory(self):
        if self.radio_button_2.isChecked():                                                  
            r = 0.048 
                                       
            self.rtU.Q[0] = self.float_values[4]
            self.rtU.Q[1] = self.float_values[5]
            self.rtU.Q[2] = self.float_values[6]
                              
            self.rtU.Q_dot[0] = (r/4)*(self.float_values[0] + self.float_values[1] + self.float_values[2] + self.float_values[3])*2*np.pi/60
            self.rtU.Q_dot[1] = (r/4)*(-self.float_values[0] + self.float_values[1] - self.float_values[2] + self.float_values[3])*2*np.pi/60
            self.rtU.Q_dot[2] = self.float_values[7]
                    
            print("{:.2f};{:.2f};{:.2f};{:.2f}".format(self.rtU.Q[0],self.rtU.Q[1],self.rtU.Q_dot[0],self.rtU.Q_dot[1]))
                          
            self.eight.last8_step()
            
            data = "{:.2f};{:.2f};{:.2f};{:.2f}\r\n".format(self.rtY.w1,self.rtY.w2,self.rtY.w3,self.rtY.w4)
            if self.radio_button_2.isChecked():
                self.esp_socket.send(data.encode("utf-8"))
                self.textEdit.setText(data)
                
            #print("{:.2f};{:.2f};{:.2f};{:.2f}".format(self.rtY.w5,self.rtY.w6,self.rtY.w7,self.rtY.w8)) 
            distances_2 = np.sqrt((self.float_values[4] - self.ref_x)**2 + (self.float_values[5] - self.ref_y)**2)
            closest_point_index_2 = np.argmin(distances_2)
            self.closest_point_x_2 = self.ref_x[closest_point_index_2]
            self.closest_point_y_2 = self.ref_y[closest_point_index_2]
        
            self.update_plot_2()
            
            self.update_error_plots(self.float_values[4],self.float_values[5],self.float_values[6],self.rtY.Tp[0],self.rtY.Tp[1],self.rtY.Tp[2],self.rtY.Tp[3])     
                                                                              
    def get_gps(self):           
        distances_2 = np.sqrt((self.float_values[4] - self.ref_x)**2 + (self.float_values[5] - self.ref_y)**2)
        closest_point_index_2 = np.argmin(distances_2)
        self.closest_point_x_2 = self.ref_x[closest_point_index_2]
        self.closest_point_y_2 = self.ref_y[closest_point_index_2]
        
        self.update_plot_2()
                      
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())