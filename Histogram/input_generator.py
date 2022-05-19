import random

with open("in.txt", 'w') as file:
    for i in range(1024000):
        file.write(f"{(random.randint(0,100))} ")