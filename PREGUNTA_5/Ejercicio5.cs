using System;
using System.Collections.Generic;
using System.Threading;

class Program{
    static List<int> Serie1(int n){
        List<int> s1 = new List<int> { n };
        for (int i = 1; i < 10000; i++){
            n += 2 * i + 1;
            s1.Add(n);
        }
        return s1;
    }

    static List<int> Serie2(){
        List<int> s2 = new List<int>();
        int inicio = 2;
        int fin = 20000;
        for (int i = inicio; i <= fin; i += 2){
            s2.Add(i);
        }
        return s2;
    }

    static List<int> seriesCombinadas(List<int> s1, List<int> s2){
        List<int> res = new List<int>();
        for (int i = 0; i < s1.Count; i++){
            res.Add(s1[i]);
            res.Add(s2[i]);
        }
        return res;
    }

    static void Main(){
        int x = 2;
        List<int> s1 = new List<int>();
        List<int> s2 = new List<int>();
        Thread thread1 = new Thread(() => s1 = Serie1(x));
        Thread thread2 = new Thread(() => s2 = Serie2());
        thread1.Start();
        thread2.Start();
        thread1.Join();
        thread2.Join();
        List<int> res1 = seriesCombinadas(s1, s2);
        foreach (int num in res1){
            Console.Write(num + " ");
        }
    }
}
