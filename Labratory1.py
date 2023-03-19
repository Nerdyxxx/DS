import sys
import time
import psutil
process = psutil.Process()
while True:
    a, b = map(int, input().split())
    if a < 2 or b > 2 * 10 ** 9:
        print("Неверное значение диапазон 2 <= A ; B <= 2 * 10^9")
    if a >= 2 and b <= 2 * 10 ** 9:
        break    
k = 1
start_time = time.time()
if b % a == 0:
    print(k)
    exit()
k+=1
while(pow(b, k) <= sys.maxsize):
    if (b ** k) % a == 0:
        print(k)
        break
    else:
        k+=1
if(pow(b, k) > sys.maxsize):
   print("-1")
memory = process.memory_info().rss
memory_mb = memory / 1024 / 1024
print("--- %s seconds ---" % (time.time() - start_time))
print(f"Используется {memory_mb:.2f} МБ памяти")