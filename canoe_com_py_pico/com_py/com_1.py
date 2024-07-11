from win32com.client import *
from win32com.client.connect import *

mApp = DispatchEx('CANoe.Application')

mMeasurement = mApp.Measurement
mSystem = mApp.System
mNamespaces = mSystem.Namespaces
mNamespace = mNamespaces.Item("FDX")
mVariables = mNamespace.Variables
mVariable = mVariables.Item("EngineSpeedEntry")