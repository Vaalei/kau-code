import random
lst = []


names = ["Poppy","Bella","Misty","Molly","Daisy","Tilly","Luna","Lily"]
class djur():
    def __init__(self, namn, typ, age) -> None:
        self.namn = namn
        self.typ = typ
        self.age = age

        lst.append(self)

n = int(input())
for i in range(n):
    namn = random.choice(names)
    typ = "katt"
    age = random.randint(1,100)
    djur(namn, typ, age)

for x in lst:
    print(x.namn)
for x in lst:
    print(x.age)




