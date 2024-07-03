import socket
from time import sleep
from struct import *

def build_Header():
    global incSequenceNumber
    fdxSignature        = b'\x43\x41\x4E\x6F\x65\x46\x44\x58'
    fdxMajorVersion     = b'\x02'
    fdxMinorVersion     = b'\x00'
    numberOfCommands    = b'\x00\x01'
    sequenceNumber      = pack('h', incSequenceNumber)
    fdxProtocolFlags    = b'\x00'
    reserved            = b'\x00'

    if (incSequenceNumber < 32767):
        incSequenceNumber = incSequenceNumber + 1
    else:
        incSequenceNumber = 1

    header = fdxSignature + fdxMajorVersion + fdxMinorVersion + numberOfCommands + sequenceNumber + fdxProtocolFlags + reserved
    return header

def start_CANoe():
    start       = b'\x04\x00\x01\x00'
    startCANoe  = build_Header() + start
    sock.sendto(startCANoe, (UDP_IP, UDP_PORT))
    # socket.sendto(startCANoe, (UDP_IP, UDP_PORT))

def stop_CANoe():
    stop        = b'\x04\x00\x02\x00'
    stopCANoe   = build_Header() + stop
    sock.sendto(stopCANoe, (UDP_IP, UDP_PORT))

def send_data (Enginespeed, EngineSwitch, Flashlight, Headlight):
    # Data Exchange
    # set data
    commandSize     = b'\x10\x00'
    commandCode     = b'\x05\x00'
    groupID         = b'\x02\x00'
    dataSize        = b'\x08\x00'
    dataBytes       = pack ('hbbbbbb', Enginespeed, EngineSwitch, Flashlight, Headlight, 0, 0, 0) 
    dataExchange    = commandSize + commandCode + groupID + dataSize + dataBytes
    sendData        = build_Header() + dataExchange
    sock.sendto(sendData, (UDP_IP, UDP_PORT))


def data_Req():
    reqCommandSize  = b'\x06\x00'
    reqCommandCode  = b'\x06\x00'
    reqGroupID      = b'\x01\x00'
    request         = reqCommandSize + reqCommandCode + reqGroupID
    reqData         = build_Header() + request
    sock.sendto(reqData, (UDP_IP, UDP_PORT))

incSequenceNumber   =0
headlight_prev      =0
flashlight_prev     =0
#socket Setup
UDP_IP              = "127.0.0.1"
UDP_PORT            = 2809
sock    = socket.socket(socket.AF_INET,#Internet
                        socket.SOCK_DGRAM)#UDP

#Start CANoe
start_CANoe()
sleep(1)

while True:
    data_Req()
    data,addr = sock.recvfrom(4096)
    # print("received message:%s\n" % data)
    sig_EngSpeed    = data[-7]<<8|data[-8]
    sig_EngSwitch   = data[-6]
    sig_Flashlight  = data[-5]
    sig_Headlight   = data[-4]
    sv_flashlight   = data[-3]
    sv_headlight    = data[-2]

    # sig_EngSpeed    =   100
    if ((sv_headlight != headlight_prev) or (sv_flashlight != flashlight_prev)):
        send_data(sig_EngSpeed, sig_EngSwitch, sig_Flashlight, sig_Headlight)
    # headlight_prev  =   sv_headlight
    # flashlight_prev =   sv_flashlight
    print("data[-1]: ", data[-1])
    print("data[-2]: ", data[-2])
    print("data[-3]: ", data[-3])
    print("data[-4]: ", data[-4])
    print("data[-5]: ", data[-5])
    print("data[-6]: ", data[-6])
    print("data[-7]: ", data[-7])
    print("data[-8]: ", data[-8])
    print("sig_EngSpeed:  " ,       sig_EngSpeed    )
    print("sig_EngSwitch: " ,       sig_EngSwitch   )
    print("sig_Flashlight:" ,       sig_Flashlight  )
    print("sig_Headlight: " ,       sig_Headlight   )
    print("sv_flashlight: " ,       sv_flashlight   )
    print("sv_headlight:  " ,       sv_headlight    )
    print("*-------------------*")
    # print("data[0]: ", data[0])
    # print("data[1]: ", data[1])
    # print("data[2]: ", data[2])
    # print("data[3]: ", data[3])
    # print("data[4]: ", data[4])
    # print("data[5]: ", data[5])
    # print("data[6]: ", data[6])
    # print("data[7]: ", data[7])
    # print("*-------------------*")

    sleep(1)
