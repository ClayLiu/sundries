import numpy as np 
import random
import math
from tqdm import tqdm

class Bounds():
    upper = 1
    lower = 0

class MatrixShapeIndex():
    row = 0
    column = 1

MatrixShapeIndex = MatrixShapeIndex()
Bounds = Bounds()

class InterationResult():
    def __init__(self, Result_dict : dict):
        self.best_position = Result_dict['best_position']
        self.best_fitness = Result_dict['best_fitness']
        self.best_fitness_value_history = Result_dict['best_fitness_value_history']

class Salp():
    def __init__(self, x_bound : np.ndarray):
        
        self.x_dim = x_bound.shape[MatrixShapeIndex.column]
        self.l_bound = x_bound[Bounds.lower]                          # x 在各维的下界
        self.u_bound = x_bound[Bounds.upper]                          # x 在各维的上界
        self.across = x_bound[Bounds.upper] - x_bound[Bounds.lower]   # x 在各维的取值跨度
        
        self.position = self.across * np.random.random_sample(self.x_dim) + self.l_bound
        self.position_new = self.position

    def update_head(self, best_position : np.ndarray, c1 : float):
        # c2 = random.random()                        # 同一随机数
        c2 = np.random.random_sample(self.x_dim)    # 每一维度不同随机数
        c3 = random.random()
        second_part = c1 * (self.across * c2 + self.l_bound)

        if c3 < 0.5:
            self.position = best_position - second_part
        else:
            self.position = best_position + second_part

    def update_other(self, prev):
        self.position += prev.position
        self.position /= 2

    def bound_check(self):
        bigger = self.position > self.u_bound
        smaller = self.position < self.l_bound

        self.position[bigger] = self.u_bound[bigger]
        self.position[smaller] = self.l_bound[smaller]

class SalpSwarm():
    def __init__(self, func, salp_num, x_bound, subject_func = None):
        '''
        :param func:            适应度函数，参数为 x 向量 \n
        :param salp_num:        樽海鞘个数 \n
        :param x_bound:         x 在各维度的取值范围，shape = (2, x_dim) \n
        :param subject_func:    约束条件函数 bool值函数\n
        '''
        self.func = func
        self.salp_num = salp_num
        self.x_bound = x_bound
        self.subject_func = subject_func

        self.salp_swarm = []
        for i in range(salp_num):
            temp_salp = Salp(x_bound)
            self.salp_swarm.append(temp_salp)

        if self.subject_func:
            self.subjections()

        self.c1_formula = lambda t, T : 2 * math.exp(- (4 * t / T)**2)

        self.fitness = np.zeros(salp_num) + 1e10
    
    def refresh_swarm(self):
        self.salp_swarm.clear()
        for i in range(self.salp_num):
            temp_salp = Salp(self.x_bound)
            self.salp_swarm.append(temp_salp)

        if self.subject_func:
            self.subjections()

    def subjections(self):
        ''' 
            检查樽海鞘是否符合约束条件，若不符则随机生成一个新樽海鞘 \n
            随机生成的也要检查是否符合，直到符合条件
        '''
        for i in range(self.salp_num):
            while not self.subject_func(self.salp_swarm[i].position):
                self.salp_swarm[i] = Salp(self.x_bound)

    def bound_check(self):
        ''' 检查樽海鞘有没有超过边界，有则拉回边界 '''
        for salp in self.salp_swarm:
            salp.bound_check()

    def get_fitness(self):
        for i, salp in enumerate(self.salp_swarm):
            self.fitness[i] = self.func(salp.position.copy())
    
    def iteration(self, iter_num, if_show_process = True) -> InterationResult:

        best_fitness_value = []

        self.get_fitness()
        best_salp_index = np.argmin(self.fitness)
        best_fitness_value.append(self.fitness[best_salp_index])
        best_position = self.salp_swarm[best_salp_index].position
        # print(best_position, self.fitness[best_salp_index])

        t_iterator = tqdm(range(1, iter_num + 1)) if if_show_process else range(1, iter_num + 1)

        for t in t_iterator:
            c_1 = self.c1_formula(t, iter_num)

            for i, single_salp in enumerate(self.salp_swarm):
                if i == 0:
                    # 链头产生新解
                    single_salp.update_head(best_position, c_1)
                else:
                    # 其他产生新解
                    single_salp.update_other(self.salp_swarm[i - 1])
            
            if self.subject_func:
                self.subjections()
            else:
                self.bound_check()
            
            self.get_fitness()
            best_salp_index = np.argmin(self.fitness)
            best_fitness_value.append(self.fitness[best_salp_index])

            best_position = self.salp_swarm[best_salp_index].position.copy()

        
        return InterationResult(
                {
                    'best_position' : best_position,
                    'best_fitness' : self.fitness[best_salp_index],
                    'best_fitness_value_history' : best_fitness_value
                }
            )





def cost(x : np.ndarray) -> float:
    return (x[0]** 2 - 2) ** 2


if __name__ == '__main__':
    search_space = np.array([
        [0],
        [2]
    ])
    solver = SalpSwarm(cost, 30, search_space)
    solution_dict = solver.iteration(100)
    solution = solution_dict['best_position']
    print('solution = ', solution[0])