"""
# My first app
Here's our first attempt at using data to create a table:
"""

import streamlit as st
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
Data_Folder_Path="../../build"
# Data_Folder_Path="."
# Data_Folder_Path="../../build"
# def file_selector(folder_path='../../build'):

# @st.cache_data
def file_selector(folder_path=Data_Folder_Path):
    # Filter to only .dat files
    filenames = [f for f in os.listdir(folder_path) if f.endswith('.dat')]
    if not filenames:
        st.warning("No .dat files found in directory")
        return None
    selected_filename = st.selectbox('Select dat file from build folder', filenames)
    file_path = os.path.join(folder_path, selected_filename)
    return file_path

# @st.cache_data
# def fetch_and_clean_data():
#     # Fetch data from URL here, and then clean it up.
#     # 添加.dat文件解析逻辑
#     filename = file_selector()
#     if filename.endswith('.dat'):
#         # 假设.dat文件使用空格分隔，包含表头
#         df_profiles = pd.read_csv(filename, sep=',',header=0)
#         # df_profiles = pd.read_csv(data_file_path)
#     else:
#         df_profiles = pd.read_csv(filename)
#     # no_samples = df_profiles.shape[0]
#     # time = np.arange(no_samples) * df_info['DOWN_SAMPLE'].values[0] * df_info['TS'].values[0]
#     # df_profiles['Time'] = time  # 添加时间列

#     return df_profiles

# df_profiles = fetch_and_clean_data()
file_path=file_selector()
st.write(file_path)
df_profiles = pd.read_csv(file_path,header=None,encoding='utf-16 LE',sep=' ')
# df_profiles = pd.read_csv(file_path,encoding='utf-16 LE',sep=' ')
st.write(df_profiles)
st.write(df_profiles.index)

fig,ax=plt.subplots(figsize=(10, 10))
ax.plot(df_profiles.index,df_profiles[0])
ax.plot(df_profiles.index,df_profiles[1])
ax.plot(df_profiles.index,df_profiles[2])
ax.plot(df_profiles.index,df_profiles[3])
st.pyplot(fig)
