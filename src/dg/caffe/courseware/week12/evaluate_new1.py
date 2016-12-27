# -*- coding: utf-8 -*-
"""
Created on Fri Nov  7 20:39:22 2014

@author: crw
"""
import sys
import numpy as np
import matplotlib.pyplot as plt

caffe_root = '/opt/DeepFace/resource/caffe-local/'
sys.path.insert(0, caffe_root + 'python')
import caffe
import cv2

from skimage import io
io.use_plugin('matplotlib')

plt.rcParams['figure.figsize'] = (10, 10)
plt.rcParams['image.interpolation'] = 'nearest'
plt.rcParams['image.cmap'] = 'gray'

itera=1500000
net = caffe.Classifier('/opt/DeepFace/FaceAlignment/try1_2/depoly.prototxt',
      '/opt/DeepFace/FaceAlignment/Model/try1_2/snapshot_iter_' +str(itera)+'.caffemodel')

net.set_phase_test()
net.set_mode_cpu()

def vis_square(data, padsize=1, padval=0):
    '''
    @brief: 定义显示函数;
    '''
    # 归一化到0-1
    data -= data.min()
    data /= data.max()
    
    # 强制使得滤波器为方形;
    n = int(np.ceil(np.sqrt(data.shape[0])))
    padding = ((0, n ** 2 - data.shape[0]), (0, padsize), (0, padsize)) + ((0, 0),) * (data.ndim - 3)
    data = np.pad(data, padding, mode='constant', constant_values=(padval, padval))
    
    # 把滤波器序列转换成图像显示;
    data = data.reshape((n, n) + data.shape[1:]).transpose((0, 2, 1, 3) + tuple(range(4, data.ndim + 1)))
    data = data.reshape((n * data.shape[1], n * data.shape[3]) + data.shape[4:])
    # 显示数据：
    plt.imshow(data)
    
def test_one(image_path):
    '''
    @brief: 测试模型，输入为图像路径
    '''
    #image=skimage.io.imread(image_path)
    image=caffe.io.load_image(image_path) 
    print image.shape
    #image=cv2.imread(image_path) 
    print image.shape
    
    scores = net.predict([image], False)
    print scores.shape
    scores = np.reshape(scores,(10,))
    print scores.shape
    print scores
    image=cv2.imread(image_path) 
    for  i in range(0,10,2):
        cv2.circle(image,(int(scores[i]),int(scores[i+1])),1,[0,0,255])
    #image = cv2.resize(image,(200,200))
    #cv2.imshow('Result',image)
    #cv2.waitKey(200)
    return image

if __name__  ==  "__main__":
    savepath= '/opt/DeepFace/FaceAlignment/Evaluate/result1/';
#    for i in range(1,200):
    image_path ='/opt/DeepFace/FaceAlignment/Evaluate/result2/141.png'
    image = test_one(image_path)
    print image.shape
    cv2.imwrite(savepath + '141.png', image)
        