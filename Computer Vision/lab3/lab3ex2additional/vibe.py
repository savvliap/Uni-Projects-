import numpy as np
import os
import cv2

def initial_background(I_gray, N):
    
    I_pad = np.pad(I_gray, 1, 'symmetric')
    height = I_pad.shape[0]
    width = I_pad.shape[1]
    samples = np.zeros((height,width,N))
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            for n in range(N):
                x, y = 0, 0
                while(x == 0 and y == 0):
                    x = np.random.randint(-1, 1)
                    y = np.random.randint(-1, 1)
                ri = i + x
                rj = j + y
                samples[i, j, n] = I_pad[ri, rj]
    samples = samples[1:height-1, 1:width-1]
    return samples
    
def vibe_detection(I_gray, samples, _min, N, R):
    
    height = I_gray.shape[0]
    width = I_gray.shape[1]
    segMap = np.zeros((height, width)).astype(np.uint8)
    for i in range(height):
        for j in range(width):
            count, index, dist = 0, 0, 0
            while count < _min and index < N:
                dist = np.abs(I_gray[i,j] - samples[i,j,index])
                if dist < R:
                    count += 1
                index += 1
            if count >= _min:
                r = np.random.randint(0, N-1)
                if r == 0:
                    r = np.random.randint(0, N-1)
                    samples[i,j,r] = I_gray[i,j]
                r = np.random.randint(0, N-1)
                if r == 0:
                    x, y = 0, 0
                    while(x == 0 and y == 0):
                        x = np.random.randint(-1, 1)
                        y = np.random.randint(-1, 1)
                    r = np.random.randint(0, N-1)
                    ri = i + x
                    rj = j + y
                    try:
                        samples[ri, rj, r] = I_gray[i, j]
                    except:
                        pass
            else:
                segMap[i, j] = 255
    return segMap, samples
    
image=cv2.imread("lab2/pedestrian/input/in000001.jpg")
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

N = 20
R = 20
_min = 2
phai = 16

samples = initial_background(image, N)

for i in range(301,1099):
    k=i+1
    I = cv2.imread("lab2/pedestrian/input/in%06d.jpg" % k)
    I_VIS = I # copy of the input image
    IG = cv2.cvtColor(I_VIS, cv2.COLOR_BGR2GRAY)
    segMap, samples = vibe_detection(IG, samples, _min, N, R)
#     cv2.imshow('segMap', segMap)
#     if cv2.waitKey(1) and 0xff == ord('q'):
#         break
# cv2.destroyAllWindows()

    cv2.imshow("vibe",segMap)
    cv2.waitKey(10)
    