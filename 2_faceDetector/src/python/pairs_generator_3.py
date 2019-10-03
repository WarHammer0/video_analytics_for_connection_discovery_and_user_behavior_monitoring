import os
import sys
import random
import shutil
from collections import defaultdict
import scipy.io as sio


full_db = open("/home/vgl-gpu/Programs/Nabil/ait-research-study/Caffe_Files/labelFri2Dec.txt",'r')

print "Wait a second. A big database is being generated, the process may take few minutes!"

labeled = defaultdict(list)

line_number=1
while 1:
    txt = full_db.readline()
    if txt == '':
        break
    source,_,label = txt.rpartition(' ')
    labeled[int(label)].append(line_number)
    line_number+=1

pos_pairs = []
neg_pairs = []
pairs1 = []
pairs2 = []
pairs3 = []
pairs4 = []
pairs5 = []
pairs6 = []
pairs7 = []
pairs8 = []
pairs9 = []
pairs10 = []
pairs11 = []
pairs12 = []
pairs13 = []
pairs14 = []
pairs15 = []
pairs16 = []
pairs17 = []
total_length_pairs = 0

#print len(labeled)-1
for k in range(1, len(labeled)-1):
    for j in range(k+1, len(labeled)):
         if labeled[k]:
          if labeled[j]:
            print k
            print j
            if total_length_pairs<=8500000:
              pairs1.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=17000000:
              pairs2.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=25500000:
              pairs3.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=34000000:
              pairs4.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=42500000:
              pairs5.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=51000000:
              pairs6.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=59500000:
              pairs7.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=68000000:
              pairs8.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=76500000:
              pairs9.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=85000000:
              pairs10.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=93500000:
              pairs11.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=102000000:
              pairs12.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=110500000:
              pairs13.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=119000000:
              pairs14.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=127500000:
              pairs15.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=136000000:
              pairs16.append([labeled[k][0],labeled[j][0]])
            elif total_length_pairs<=144500000:
              pairs17.append([labeled[k][0],labeled[j][0]])
            total_length_pairs+=1
            

#print total_length_pairs
dic1 = {'pair':pairs1}
dic2 = {'pair':pairs2}
dic3 = {'pair':pairs3}
dic4 = {'pair':pairs4}
dic5 = {'pair':pairs5}
dic6 = {'pair':pairs6}
dic7 = {'pair':pairs7}
dic8 = {'pair':pairs8}
dic9 = {'pair':pairs9}
dic10 = {'pair':pairs10}
dic11 = {'pair':pairs11}
dic12 = {'pair':pairs12}
dic13 = {'pair':pairs13}
dic14 = {'pair':pairs14}
dic15 = {'pair':pairs15}
dic16 = {'pair':pairs16}
dic17 = {'pair':pairs17}

sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_1.mat", dic1)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_2.mat", dic2)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_3.mat", dic3)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_4.mat", dic4)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_5.mat", dic5)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_6.mat", dic6)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_7.mat", dic7)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_8.mat", dic8)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_9.mat", dic9)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_10.mat", dic10)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_11.mat", dic11)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_12.mat", dic12)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_13.mat", dic13)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_14.mat", dic14)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_15.mat", dic15)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_16.mat", dic16)
sio.savemat("/home/vgl-gpu/Programs/Nabil/ait-research-study/src/face_id/face_verification_experiment-master/code/homkrun_Fri2Dec_pair_17.mat", dic17)


full_db.close()
