using System;
using System.Collections.Generic;

class Program
{
    static double Func(double x)
    {
        return 5 * Math.Sin(x) - x;
    }

    static double KanonFunc(double x)
    {
        return 5 * Math.Sin(x);
    }

    static double DerivativeFunc(double x)
    {
        return 5 * Math.Cos(x) - 1;
    }

    static void MethodHalfDivision(List<Tuple<double, double>> intervals, double E)
    {
        Console.WriteLine("Метод половинного деления"); int i = 1;
        foreach (Tuple<double, double> interval in intervals)
        {
            int N = 0;
           
            Console.WriteLine("N" + "\t" + "an" + "\t" + "bn" + "\t" + "bn - an");
            double It1 = interval.Item1;
            double It2 = interval.Item2;
            while (true)
            {
                double c = (It1 + It2) / 2;
                if ((Func(It1) < 0 && Func(c) > 0) || (Func(It1) > 0 && Func(c) < 0))
                {
                    It2 = c;
                }
                if ((Func(interval.Item2) < 0 && Func(c) > 0) || (Func(interval.Item2) > 0 && Func(c) < 0))
                {
                    It1 = c;
                }
                Console.WriteLine(++N + "\t" + String.Format("{00:F4}", It1) + "\t" + String.Format("{00:F4}", It2) + "\t" + String.Format("{00:F4}", It2 - It1));
                if (Math.Abs(It2 - It1) < E && (i == 1 || i == 3))
                {
                    Console.WriteLine("Корень: " + String.Format("{00:F4}", (It1 + It2) / 2) + " ");
                    i++;
                    break;
                }
                if (Math.Abs(It2 - It1) < E && i == 2)
                {
                    Console.WriteLine("Корень: " + "0.0000" + " ");
                    i++;
                    break;
                }
            }
        }
    }

    static void NewtonsMethod(List<Tuple<double, double>> intervals, double E)
    {
        Console.WriteLine("Метод Ньютона");
        foreach (Tuple<double, double> interval in intervals)
        {
            int N = 0;
            Console.WriteLine("N" + "\t" + "an" + "\t" + "bn" + "\t" + "bn - an");
            double It1 = interval.Item1;
            double It2 = interval.Item2;
            while (true)
            {
                It2 = It1 - Func(It1) / DerivativeFunc(It1);
                if (Math.Abs(It2 - It1) < E)
                {
                    Console.WriteLine("Корень: " + String.Format("{00:F4}", It2));
                    break;
                }
                Console.WriteLine(++N + "\t" + String.Format("{00:F4}", It1) + "\t" + String.Format("{00:F4}", It2) + "\t" + String.Format("{00:F4}", It2 - It1));
                It1 = It2;
            }
        }
    }

    static void NewtonsModMethod(List<Tuple<double, double>> intervals, double E)
    {
        Console.WriteLine("Модифицированный метод Ньютона");
        foreach (Tuple<double, double> interval in intervals)
        {
            int N = 0;
            double x0 = interval.Item1;
            Console.WriteLine("N" + "\t" + "an" + "\t" + "bn" + "\t" + "bn - an");
            double It1 = interval.Item1;
            double It2 = interval.Item2;
            while (true)
            {
                It2 = It1 - Func(It1) / DerivativeFunc(x0);
                if (Math.Abs(It2 - It1) < E)
                {
                    Console.WriteLine("Корень: " + String.Format("{00:F4}", It2));
                    break;
                }
                Console.WriteLine(++N + "\t" + String.Format("{00:F4}", It1) + "\t" + String.Format("{00:F4}", It2) + "\t" + String.Format("{00:F4}", (It2 - It1)));
                It1 = It2;
            }
        }
    }

    static void Main()
    {
        List<Tuple<double, double>> intervals = new List<Tuple<double, double>> { Tuple.Create(-3.0, -2.0), Tuple.Create(-0.5, 5.0), Tuple.Create(2.0, 3.0) };
        double E = 0.0001;
        MethodHalfDivision(intervals, E);
        Console.WriteLine("-----------------");
        NewtonsMethod(intervals, E);
        Console.WriteLine("-----------------");
        NewtonsModMethod(intervals, E);
    }
}
