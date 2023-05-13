def sudoku_checker(solution):

    valid = True
    s_lim = 9

    # horizontal
    for i in range(s_lim):
        for j in range(s_lim - 1):
            for k in range(j+1,s_lim):
                if solution[i][j] == solution[i][k] and solution[i][j] != 0:
                    print(i,j,k)
                    return False

    # vertical
    for i in range(s_lim):
        for j in range(s_lim - 1):
            for k in range(j+1,s_lim):
                if solution[j][i] == solution[k][i] and solution[j][i] != 0:
                    print(i,j,k)
                    return False

    # block
    for i in range(s_lim//3): # block row
        for j in range(s_lim//3): # block col
            for m in range(s_lim-1):
                for n in range(m+1,s_lim):
                    
                    m_row_idx = i * 3 + m // 3
                    m_col_idx = j * 3 + m % 3
                    n_row_idx = i * 3 + n // 3
                    n_col_idx = j * 3 + n % 3

                    if solution[m_row_idx][m_col_idx] == solution[n_row_idx][n_col_idx] and solution[m_row_idx][m_col_idx] != 0:
                        print(m_row_idx,m_col_idx,n_row_idx,n_col_idx)
                        return False

    return valid


sol1 = []
sol1.append([5,3,0,0,7,0,0,0,0])
sol1.append([6,0,0,1,9,5,0,0,0])
sol1.append([0,9,8,0,0,0,0,6,0])
sol1.append([8,0,0,0,6,0,0,0,3])
sol1.append([4,0,0,8,0,3,0,0,1])
sol1.append([7,0,0,0,2,0,0,0,6])
sol1.append([0,6,0,0,0,0,2,8,0])
sol1.append([0,0,0,4,1,9,0,0,5])
sol1.append([0,0,0,0,8,0,0,7,9])

# invalid (horizontal)
sol2 = []
sol2.append([5,3,0,0,5,0,0,0,0])
sol2.append([6,0,0,1,9,5,0,0,0])
sol2.append([0,9,8,0,0,0,0,6,0])
sol2.append([8,0,0,0,6,0,0,0,3])
sol2.append([4,0,0,8,0,3,0,0,1])
sol2.append([7,0,0,0,2,0,0,0,6])
sol2.append([0,6,0,0,0,0,2,8,0])
sol2.append([0,0,0,4,1,9,0,0,5])
sol2.append([0,0,0,0,8,0,0,7,9])

# invalid (vertical)
sol3 = []
sol3.append([5,3,0,0,7,0,0,0,0])
sol3.append([6,0,0,1,9,5,0,0,0])
sol3.append([0,9,8,0,0,0,0,6,0])
sol3.append([8,0,0,0,6,0,0,0,3])
sol3.append([4,0,0,8,0,3,0,0,1])
sol3.append([7,0,0,0,2,0,0,0,6])
sol3.append([0,6,0,0,0,0,2,8,0])
sol3.append([0,0,0,4,1,9,2,0,5])
sol3.append([0,0,0,0,8,0,0,7,9])

# invalid (block)
sol4 = []
sol4.append([5,3,0,0,7,0,0,0,0])
sol4.append([6,0,0,1,9,5,0,0,0])
sol4.append([0,9,8,0,0,0,0,6,0])
sol4.append([8,0,0,0,6,0,0,0,3])
sol4.append([4,0,0,8,0,3,0,0,1])
sol4.append([7,0,0,0,2,0,0,0,6])
sol4.append([0,6,0,0,0,0,2,8,0])
sol4.append([0,0,0,4,1,9,0,0,5])
sol4.append([0,0,6,0,8,0,0,7,9])


print(sudoku_checker(sol1))
print(sudoku_checker(sol2))
print(sudoku_checker(sol3))
print(sudoku_checker(sol4))