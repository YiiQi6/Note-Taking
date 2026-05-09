import numpy as np
import pandas as pd
from sklearn.model_selection import  train_test_split
from sklearn.preprocessing import  MinMaxScaler
from sklearn.linear_model import  LogisticRegression
from sklearn.metrics import  classification_report
from sklearn import  datasets

# 加载威斯康星州乳腺癌数据集
cancer_data = datasets.load_breast_cancer()

# 特征数据
X = cancer_data.data

# 目标变量
Y = cancer_data.target

# 划分数据集和测试集
x_train,x_test,y_train,y_test = train_test_split(X,Y,test_size=0.2)

# 数据归一化
sc = MinMaxScaler(feature_range=(0,1))
x_train = sc.fit_transform(x_train)
x_test = sc.fit_transform(x_test)

# 逻辑回归模型搭建
lr= LogisticRegression()
lr.fit(x_train,y_train)

# 打印模型的参数
print('w:',lr.coef_)
print('b:',lr.intercept_)

# 利用训练好的模型进行推理测试
pre_result = lr.predict(x_test)

# 打印预测结果的概率
pre_result_proba = lr.predict_proba(x_test)

# 获取恶性肿瘤的概率
pre_list = pre_result_proba[:,1]

# 设置阈值
thresholds = 0.3

# 设置保存结果的列表
result =[]
result_name =[]

for i in range(len(pre_list)):
    if pre_list[i] > thresholds:
        result.append(1)
        result_name.append('恶性')
    else:
        result.append(0)
        result_name.append('良性')

print(result_name)

# 模型评估
report = classification_report(y_test,result,labels=[0,1],target_names=['良性','恶性'])
print(report)