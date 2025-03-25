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

def file_selector(folder_path, label, key):
    filenames = [f for f in os.listdir(folder_path) if f.endswith('.dat')]
    if not filenames:
        st.warning("No .dat files found in directory")
        return None
    selected_file = st.selectbox(label, filenames, key=key)
    return os.path.join(folder_path, selected_file)

with st.sidebar:
    st.markdown("---")
    file_path_1 = file_selector(Data_Folder_Path, 'Select first data file', 'file1')
    st.write(file_path_1)
    
    # st.markdown("---")
    # file_path_2 = file_selector(Data_Folder_Path, 'Select second data file', 'file2')
    # st.write(file_path_2)
df_profiles = pd.read_csv(file_path_1, sep=' ')
st.write(df_profiles)
# plot all in one figure
# [Data_1 Data_2 ...] in one figure
# fig, ax = plt.subplots(figsize=(10, 10))
# for col in df_profiles.columns:  # Use actual column headers
#     ax.plot(df_profiles[col], label=col)  # Plot using header names
# ax.grid(True)
# ax.legend()
# st.pyplot(fig)

# plot each in each figure
# [Data_1 Data_2 ...] in every independent figure
# for col in df_profiles.columns:  # Use actual column headers
#     fig, ax = plt.subplots(figsize=(10, 10))
#     ax.plot(df_profiles[col], label=col)  # Plot using header names
#     ax.grid(True)
#     ax.legend()
#     st.pyplot(fig)

# plot Time serial with other data in one figure
# [Time Data_1 Data_2 ...]
fig, ax = plt.subplots(figsize=(20, 10))
time_values = df_profiles.iloc[:, 0]
data_columns = df_profiles.columns[1:]
for col in data_columns:  # Use actual column headers
    ax.plot(time_values, df_profiles[col], label=col)
ax.grid(True)
ax.set_xlabel(df_profiles.columns[0])  # Set X-axis label to first column name
ax.legend()
st.pyplot(fig)

# fig, ax = plt.subplots(figsize=(10, 10))
# for col in df_profiles.columns:  # Use actual column headers
#     ax.plot(df_profiles[col], label=col)  # Plot using header names
# ax.grid(True)
# ax.legend()
# st.pyplot(fig)

