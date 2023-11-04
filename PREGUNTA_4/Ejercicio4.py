import multiprocessing

def gSerie1(n):
    s1 = [n]
    for i in range(1, 10000):
        n += 2 * i + 1
        s1.append(n)
    return s1

def gSerie2():
    inicio = 2
    fin = 20000  
    s2 = list(range(inicio, fin + 2, 2))
    return s2

def combSeries(serie1, serie2):
    serie_aux = [x for y in zip(s1, s2) for x in y]
    return serie_aux

if __name__ == "__main__":
    pool = multiprocessing.Pool()
    # la serie inicia con 2 como el primer termino
    res_serie1 = pool.apply_async(gSerie1, (2,))  
    res_serie2 = pool.apply_async(gSerie2)
    s1 = res_serie1.get()
    s2 = res_serie2.get()
    res = combSeries(s1, s2)
    print(res)

