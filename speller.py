from dictionary import Dictionary
import time

# Create an instance
dic = Dictionary()

start = time.process_time()
load_stts = dic.load("dictionaries/small")
end = time.process_time()
print(f"Loading(walclock) time: {end - start}")

check_stts = dic.check("caterpillar")

print(load_stts)
print(check_stts)

