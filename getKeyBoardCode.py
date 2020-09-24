#-*-coding:utf-8-*-
import numpy as np

def calcBinary(arr):
    s = 0
    for i in range(4):
        s += arr[i] * (2 ** i)
    return int(s)

if __name__ == "__main__":
    mapping = dict()        # 字符映射
    for i in range(10):
        mapping[i] = str(i)
    for i in range(6):
        mapping[i + 10] = chr(65 + i)

    for i in range(4):
        for j in range(4):
            highs = np.ones(4, dtype = int)
            lows = np.ones(4, dtype = int)
            highs[i] = 0        # 高位为行
            lows[j] = 0         # 低位为列
            print("pos (%d, %d): 0x%s%s"%(i, j, mapping[calcBinary(highs)], mapping[calcBinary(lows)]))
