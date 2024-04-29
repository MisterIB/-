using System;
using System.Collections.Generic;

class Program
{
    static void ScoringPoints(ref int pointFirstAlgorithm, ref int pointSecondAlgorithm, List<bool> firstAlgorithm, List<bool> secondAlgorithm)
    {
        for (int i = 0; i < firstAlgorithm.Count; i++)
        {
            if (firstAlgorithm[i] && secondAlgorithm[i])
            {
                pointFirstAlgorithm += 24;
                pointSecondAlgorithm += 24;
            }
            if (!firstAlgorithm[i] && !secondAlgorithm[i])
            {
                pointFirstAlgorithm += 4;
                pointSecondAlgorithm += 4;
            }
            if (!firstAlgorithm[i] && secondAlgorithm[i])
            {
                pointFirstAlgorithm += 20;
            }
            if (firstAlgorithm[i] && !secondAlgorithm[i])
            {
                pointSecondAlgorithm += 20;
            }
        }
    }

    static bool AlgorithmOne(int roundNumber, List<bool> selfChoices, List<bool> enemyChoices)
    {
        int countEnemyFalse = 0;
        int countEnemyTrue = 0;
        foreach (bool choices in enemyChoices)
        {
            if (choices)
                countEnemyTrue++;
            else
                countEnemyFalse++;
        }
        if (countEnemyFalse > countEnemyTrue)
            return false;
        if (countEnemyFalse < countEnemyTrue)
            return true;
        return true;
    }

    static bool AlgorithmTwo(int roundNumber, List<bool> selfChoices, List<bool> enemyChoices)
    {
        int myPointAlgorithm = 0;
        int enemyPointAlgorithm = 0;
        ScoringPoints(ref myPointAlgorithm, ref enemyPointAlgorithm, selfChoices, enemyChoices);
        if (roundNumber < 75)
        {
            if (myPointAlgorithm < enemyPointAlgorithm)
                return true;
            if (myPointAlgorithm > enemyPointAlgorithm)
                return false;
            return true;
        }
        else
        {
            if (myPointAlgorithm < enemyPointAlgorithm)
                return false;
            if (myPointAlgorithm > enemyPointAlgorithm)
                return true;
            return false;
        }
    }

    static bool AlgorithmThree(int roundNumber, List<bool> selfChoices, List<bool> enemyChoices)
    {
        if (roundNumber % 2 == 0)
            return true;
        if (roundNumber % 3 == 0 || roundNumber % 25 == 0)
            return false;
        if (roundNumber % 100 == 0)
            return true;
        return true;
    }

    static int GenerateNumRounds()
    {
        Random random = new Random();
        while (true)
        {
            int numberRounds = random.Next(0, 201);
            if (numberRounds >= 100)
            {
                Console.WriteLine("Количество раундов: " + numberRounds);
                return numberRounds;
            }
        }
    }

    static void BattleOne(List<bool> firstAlgorithm, List<bool> secondAlgorithm)
    {
        int numberRounds = GenerateNumRounds();

        for (int i = 1; i < numberRounds; i++)
        {
            firstAlgorithm.Add(AlgorithmOne(i, firstAlgorithm, secondAlgorithm));
            secondAlgorithm.Add(AlgorithmTwo(i, secondAlgorithm, firstAlgorithm));
        }
    }

    static void BattleTwo(List<bool> firstAlgorithm, List<bool> secondAlgorithm)
    {
        int numberRounds = GenerateNumRounds();

        for (int i = 1; i < numberRounds; i++)
        {
            firstAlgorithm.Add(AlgorithmThree(i, firstAlgorithm, secondAlgorithm));
            secondAlgorithm.Add(AlgorithmTwo(i, secondAlgorithm, firstAlgorithm));
        }
    }

    static void BattleThree(List<bool> firstAlgorithm, List<bool> secondAlgorithm)
    {
        int numberRounds = GenerateNumRounds();

        for (int i = 1; i < numberRounds; i++)
        {
            firstAlgorithm.Add(AlgorithmThree(i, firstAlgorithm, secondAlgorithm));
            secondAlgorithm.Add(AlgorithmOne(i, secondAlgorithm, firstAlgorithm));
        }
    }

    static void BattleAlgorithms((int, int) algorithms)
    {
        List<bool> firstAlgorithm = new List<bool>();
        List<bool> secondAlgorithm = new List<bool>();
        int pointFirstAlgorithm = 0;
        int pointSecondAlgorithm = 0;
        if (algorithms.Item1 == 1 && algorithms.Item2 == 2)
            BattleOne(firstAlgorithm, secondAlgorithm);
        if (algorithms.Item1 == 2 && algorithms.Item2 == 3)
            BattleTwo(firstAlgorithm, secondAlgorithm);
        if (algorithms.Item1 == 1 && algorithms.Item2 == 3)
            BattleThree(firstAlgorithm, secondAlgorithm);
        ScoringPoints(ref pointFirstAlgorithm, ref pointSecondAlgorithm, firstAlgorithm, secondAlgorithm);
        Console.WriteLine("Очки первого алгоритма: " + pointFirstAlgorithm + "\nОчки второго алгоритма: " + pointSecondAlgorithm);
    }

    static void Main()
    {
        (int, int) algorithms;
        Console.WriteLine("Выберите 2 алгоритма");
        algorithms.Item1 = int.Parse(Console.ReadLine());
        algorithms.Item2 = int.Parse(Console.ReadLine());
        BattleAlgorithms(algorithms);
    }
}
