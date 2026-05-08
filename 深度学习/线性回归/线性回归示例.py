# 定义数据集

# 定义数据特征
x_data = [1,2,3]

# 定义数据标签
y_data = [2,4,6]

# 初始化w参数
w = 4

# 定义线性回归模型
def forword(x):
    return x*w

# 定义损失函数
def cost(xs,ys):
    costvalue = 0
    for x,y in zip(xs,ys):
        y_pred = forword(x) #预测值
        costvalue+=(y_pred-y)**2
    return costvalue/len(xs)

# 定义计算梯度的函数
def gradient(xs,ys):
    grad = 0
    for x,y in zip(xs,ys):
        grad+=2*x*(x*w-y)
    return grad/len(xs)

for epoch in range(100):

    #更新 损失函数值
    cost_val = cost(x_data,y_data)

    #更新梯度
    grad= gradient(x_data,y_data)

    #更新 w
    w=w-0.01*grad

    print("训练次数：",epoch,"w=",w," loss=",cost_val)


