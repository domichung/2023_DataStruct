s = "I love you and you love him and who loves who"
#字串
print(s.split())
#字串分割
print(set(s.split()))
#字串分割 並且把相同的拔掉(儲存元素)

keys = len(set(s.split()))
#算出有幾個東西

word_list = s.split()  
word_set = set(word_list)  

word_count_dict = {}  

for word in word_set:
    word_count_dict[word] = 0

print(word_count_dict)  

for word in word_set:
    word_count_dict[word] = word_list.count(word)  

print(word_count_dict)
