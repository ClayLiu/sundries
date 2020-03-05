def ysf_win(total_num : int, kill_num : int, survive_count = 1):
    dp = [0] * (total_num + 1)

    dp[2] = (kill_num & 1) + 1
    
    for i in range(3, total_num + 1):
        d_i = kill_num % i
        if d_i == 0:
            d_i = i

        dp[i] = (dp[i - 1] + d_i) % i
        if dp[i] == 0:
            dp[i] = i

    
    return dp[total_num]

def ysf_clever(total_num : int, kill_num : int, survive_count = 1):
    dp = [0] * (total_num + 1)
    for i in range(1, total_num + 1):
        dp[i] = (dp[i - 1] + kill_num) % i
    return dp[total_num] + 1

class peple_node():
    def __init__(self, order : int, prev, next):
        self.prev = prev
        self.order = order
        self.next = next 
    
    def kill_self(self):
        self.prev.next = self.next
        self.next.prev = self.prev

def ysf_run(total_num : int, kill_num : int, survive_count = 1):
    people = [1] * total_num
    count = 0
    current_survive_count = total_num
    
    while current_survive_count > survive_count:
        for i in range(total_num):
            
            if people[i] != 0:    # 未死就报数
                count += 1 
            
            if count == kill_num:
                people[i] = 0 # 报到3，杀
                current_survive_count -= 1
                count = 0   # 将报出的数设为0， 那么下一个人报的就是1

    survive = []
    for i, if_dead in enumerate(people):
        if if_dead != 0:
            survive.append(i + 1)

    return survive

def ysf_run_in_new_data(total_num : int, kill_num : int, survive_count = 1):
    temp_list = [peple_node(1, None, None)]
    for i in range(1, total_num):
        temp_list.append(peple_node(i + 1, temp_list[i - 1], None))
    
    temp_list[0].prev = temp_list[-1]

    for i in range(total_num - 1):
        temp_list[i].next = temp_list[i + 1]
    temp_list[total_num - 1].next = temp_list[0]

    current_people = temp_list[0]
    current_surivive = total_num
    while current_surivive > survive_count:
        
        for i in range(kill_num - 1):
            current_people = current_people.next
        
        next_people = current_people.next
        current_people.kill_self()
        current_people = next_people
        current_surivive -= 1
    
    return current_people.order

if __name__ == '__main__':
    total_num = 1000000
    # test = ysf_run(total_num, 5)
    # print(test[0])
    
    test_dp = ysf_win(total_num, 5)
    test_clever = ysf_clever(total_num, 5)
    print(test_dp, test_clever)
