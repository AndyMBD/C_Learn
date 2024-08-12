# https://support.vector.com/kb?id=kb_article_view&sysparm_article=KB0012474&sys_kb_id=3735c2681b2614148e9a535c2e4bcba0&spa=1
import time, os, msvcrt,sys
from win32com.client import *
from win32com.client.connect import *
mApp = DispatchEx('CANoe.Application')
mMeasurement    =   mApp.Measurement
mSystem         =   mApp.System
mNamespaces     =   mSystem.Namespaces
mNamespace      =   mNamespaces.Item("python")
mVariables      =   mNamespace.Variables
m_voltage       =   mVariables.Item("voltage")
m_current       =   mVariables.Item("current")
m_py_exit       =   mVariables.Item("py_exit")

# while not msvcrt.kbhit():
#     # bmw_test = app.get_EnvVar("en_bmw_test")
#     # print(bmw_test)
#     # if(bmw_test==2):
#     #     app.set_EnvVar("en_bmw_test",10)

#     print(m_voltage.Value)
#     print(m_py_exit.Value)
#     time.sleep(0.1)
#     if (m_py_exit== int(1)):
#         sys.exit()

# while True:
while not msvcrt.kbhit():
# if msvcrt.kbhit():
    time.sleep(0.5)
    print("******************")
    print('voltage = ', m_voltage.Value)
    # print(m_py_exit.Value)
    # print(int(1))
    print("******************")
    if (m_py_exit.Value):
        # quit(1)
        # quit()
        exit()
        # sys.exit(1)
