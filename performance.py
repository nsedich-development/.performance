#pyinstaller 

import time
start_time = time.time()

sum = int(0)
sum2 = int(0)
sum3 = int(0)

for i in range(11500000000):
    sum += i
    
print(sum)
print("--- %s seconds ---" % (time.time() - start_time))

time.sleep(10)

    