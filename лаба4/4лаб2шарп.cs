using System;
using System.Collections.Generic;

namespace CodeConversion
{
    class Program
    {
        static void Main(string[] args)
        {
            Random generator = new Random();
            int n;
            Console.WriteLine("Введите n");
            n = Convert.ToInt32(Console.ReadLine());
            List<int> arr1 = new List<int>();
            List<int> arr2 = new List<int>();
            List<char> arr3 = new List<char>();
            List<int> arr4 = new List<int>();
            InitializingArray(arr2, arr1, generator, n);
            InitializingArray(arr3, generator);
            InitializingArray(arr4, generator);
            Console.WriteLine("Массив arr1: " + string.Join(" ", arr1));
            Console.WriteLine("Массив arr2: " + string.Join(" ", arr2));
            OutputEvenNum(arr1);
            ComparingArrays(arr1, arr2);
            Console.WriteLine("Массив случайных символов: " + string.Join(" ", arr3));
            Console.WriteLine("Массив случайных символов после модификации: " + string.Join(" ", ModificationArray(arr3, 5)));
            Console.WriteLine("Массив arr4: " + string.Join(" ", arr4));
            Console.WriteLine("Сумма элементов массива arr4: " + CalculatingAmount(arr4));
            SwapPlaces(arr4);
            Console.WriteLine("Массив arr4 с отсортированными цифрами в элементах: " + string.Join(" ", arr4));
            Sort(arr4, 20);
            Console.WriteLine("Отсортированный массив arr4: " + string.Join(" ", arr4));
            Console.WriteLine("Сумма элементов массива arr4 после модификаций: " + CalculatingAmount(arr4));
        }

        static void InitializingArray(List<int> arr2, List<int> arr1, Random generator, int n)
        {
            while (arr1.Count != n)
            {
                int num = generator.Next() % 30;
                if (num >= 10)
                {
                    arr1.Add(num);
                }
            }
            while (arr2.Count != 5)
            {
                int num = generator.Next() % 30;
                if (num >= 10)
                {
                    arr2.Add(num);
                }
            }
        }

        static void InitializingArray(List<char> arraySymbols, Random generator)
        {
            while (arraySymbols.Count != 5)
            {
                char num = (char)(generator.Next() % 127);
                if (num >= 33)
                {
                    arraySymbols.Add(num);
                }
            }
        }

        static void InitializingArray(List<int> arr4, Random generator)
        {
            while (arr4.Count != 20)
            {
                int num = generator.Next() % 9000;
                if (num >= 1000)
                {
                    arr4.Add(num);
                }
            }
        }

        static void OutputEvenNum(List<int> arr1)
        {
            int elementIndex = 0;
            int countEvenElements = 0;
            Console.Write("Четные числа на нечетных местах: ");
            foreach (int element in arr1)
            {
                if (elementIndex % 2 != 0 && element % 2 == 0)
                {
                    Console.Write(element + " ");
                    countEvenElements++;
                }
                elementIndex++;
            }
            Console.WriteLine("\nКоличество четных чисел на нечетных местах: " + countEvenElements);
        }

        static void ComparingArrays(List<int> arr1, List<int> arr2)
        {
            int countRepeatNum = 0;
            foreach (int elementArr2 in arr2)
            {
                int numRepetitions = 0;
                foreach (int elementArr1 in arr1)
                {
                    if (elementArr1 == elementArr2)
                    {
                        numRepetitions++;
                    }
                }
                if (numRepetitions > 0)
                {
                    Console.WriteLine("Число: " + elementArr2 + " повторяется " + numRepetitions + " раз");
                    countRepeatNum++;
                }
            }
            if (countRepeatNum == 0)
            {
                Console.WriteLine("В массивах нет одинаковых элементов");
            }
        }

        static List<char> ModificationArray(List<char> arraySymbols, int n)
        {
            char firstElement = arraySymbols[0];
            for (int i = 0; i < n - 1; i++)
            {
                arraySymbols[i] = arraySymbols[i + 1];
            }
            arraySymbols[n - 1] = firstElement;
            return arraySymbols;
        }

        static int CalculatingAmount(List<int> arr4)
        {
            int sum = 0;
            foreach (int element in arr4)
            {
                sum += element;
            }
            return sum;
        }

        static void Sort(List<int> figures, int n)
        {
            for (int i = 0; i < n - 1; i++)
            {
                int k = i;
                for (int j = i + 1; j < n; j++)
                {
                    if (figures[j] < figures[k])
                    {
                        k = j;
                    }
                }
                int c = figures[k];
                figures[k] = figures[i];
                figures[i] = c;
            }
        }

        static void SwapPlaces(List<int> arr4)
        {
            for (int i = 0; i < arr4.Count; i++)
            {
                List<int> figures = new List<int>();
                int element = arr4[i];
                while (element > 0)
                {
                    figures.Add(element % 10);
                    element /= 10;
                }
                Sort(figures, 4);
                element = 0;
                foreach (int figure in figures)
                {
                    element = element * 10 + figure;
                }
                arr4[i] = element;
            }
        }
    }
}
