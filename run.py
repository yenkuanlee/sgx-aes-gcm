import time
import os


print("start to run sha256/4k...")
start = time.time()
os.system("./bin/sha256_4k")
end = time.time()
spend = end - start
print("using "+str(spend)+" seconds")
print("performance: "+str(float(4000)/spend)+" MB")
print("")

print("start to run sha256/1m...")
start = time.time()
os.system("./bin/sha256_1m")
end = time.time()
spend = end - start
print("using "+str(spend)+" seconds")
print("performance: "+str(float(1000000)/spend)+" MB")
print("")

print("start to run aes/4k...")
start = time.time()
os.system("./bin/aes_4k")
end = time.time()
spend = end - start
print("using "+str(spend)+" seconds")
print("performance: "+str(float(4000)/spend)+" MB")
print("")

print("start to run aes/1m...")
start = time.time()
os.system("./bin/aes_1m")
end = time.time()
spend = end - start
print("using "+str(spend)+" seconds")
print("performance: "+str(float(1000000)/spend)+" MB")
print("")

