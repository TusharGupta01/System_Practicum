import time
import random
import threading
 

# using System;
# using System.Collections.Generic;
# using System.Linq;
# using System.Text;
# using System.Threading;
# using System.Threading.Tasks;
 
# namespace Dining_Philosophers
# {
#     class Program
#     {
#         private const int DinerCount = 5;
#         private static List<Diner> Diners = new List<Diner>();
#         private static List<Fork> Forks = new List<Fork>();
#         private static DateTime TimeToStop;
 
#         static void Main(string[] args)
#         {
#             Initialize();
#             WriteHeaderLine();
 
#             do
#             {
#                 WriteStatusLine();
#                 Thread.Sleep(1000);
#             }
#             while (DateTime.Now < TimeToStop);
 
#             TearDown();
#         }
 
#         private static void Initialize()
#         {
#             for (int i = 0; i < DinerCount; i++)
#                 Forks.Add(new Fork());
#             for (int i = 0; i < DinerCount; i++)
#                 Diners.Add(new Diner(i, Forks[i], Forks[(i + 1) % DinerCount]));
 
#             TimeToStop = DateTime.Now.AddSeconds(60);
#         }
 
#         private static void TearDown()
#         {
#             foreach (var diner in Diners)
#                 diner.Dispose();
#         }
 
#         private static void WriteHeaderLine()
#         {
#             Console.Write("|");
 
#             foreach (Diner d in Diners)
#                 Console.Write("D " + d.ID + "|");
 
#             Console.Write("    |");
 
#             for (int i = 0; i < DinerCount; i++)
#                 Console.Write("F" + i + "|");
 
#             Console.WriteLine();
#         }
 
#         private static void WriteStatusLine()
#         {
#             Console.Write("|");
 
#             foreach (Diner d in Diners)
#                 Console.Write(FormatDinerState(d) + "|");
 
#             Console.Write("    |");
 
#             foreach (Fork f in Forks)
#                 Console.Write(FormatForkState(f) + "|");
 
#             Console.WriteLine();
#         }
 
#         private static string FormatDinerState(Diner diner)
#         {
#             switch (diner.State)
#             {
#                 case Diner.DinerState.Eating:
#                     return "Eat";
#                 case Diner.DinerState.Pondering:
#                     return "Pon";
#                 case Diner.DinerState.TryingToGetForks:
#                     return "Get";
#                 default:
#                     throw new Exception("Unknown diner state.");
#             }
#         }
 
#         private static string FormatForkState(Fork fork)
#         {
#             return (!ForkIsBeingUsed(fork) ? "  " : "D" + GetForkHolder(fork));
#         }
 
#         private static bool ForkIsBeingUsed(Fork fork)
#         {
#             return Diners.Count(d => d.CurrentlyHeldForks.Contains(fork)) > 0;
#         }
 
#         private static int GetForkHolder(Fork fork)
#         {
#             return Diners.Single(d => d.CurrentlyHeldForks.Contains(fork)).ID;
#         }
#     }
 
#     class Diner : IDisposable
#     {
#         private bool IsCurrentlyHoldingLeftFork = false;
#         private bool IsCurrentlyHoldingRightFork = false;
#         private const int MaximumWaitTime = 100;
#         private static Random Randomizer = new Random();
#         private bool ShouldStopEating = false;
 
#         public int ID { get; private set; }
#         public Fork LeftFork { get; private set; }
#         public Fork RightFork { get; private set; }
#         public DinerState State { get; private set; }
 
#         public IEnumerable<Fork> CurrentlyHeldForks
#         {
#             get
#             {
#                 var forks = new List<Fork>();
#                 if (IsCurrentlyHoldingLeftFork)
#                     forks.Add(LeftFork);
#                 if (IsCurrentlyHoldingRightFork)
#                     forks.Add(RightFork);
#                 return forks;
#             }
#         }
 
#         public Diner(int id, Fork leftFork, Fork rightFork)
#         {
#             InitializeDinerState(id, leftFork, rightFork);
#             BeginDinerActivity();
#         }
 
#         private void KeepTryingToEat()
#         {
#             do
#                 if (State == DinerState.TryingToGetForks)
#                 {
#                     TryToGetLeftFork();
#                     if (IsCurrentlyHoldingLeftFork)
#                     {
#                         TryToGetRightFork();
#                         if (IsCurrentlyHoldingRightFork)
#                         {
#                             Eat();
#                             DropForks();
#                             Ponder();
#                         }
#                         else
#                         {
#                             DropForks();
#                             WaitForAMoment();
#                         }
#                     }
#                     else
#                         WaitForAMoment();
#                 }
#                 else
#                     State = DinerState.TryingToGetForks;
#             while (!ShouldStopEating);
#         }
 
#         private void InitializeDinerState(int id, Fork leftFork, Fork rightFork)
#         {
#             ID = id;
#             LeftFork = leftFork;
#             RightFork = rightFork;
#             State = DinerState.TryingToGetForks;
#         }
 
#         private async void BeginDinerActivity()
#         {
#             await Task.Run(() => KeepTryingToEat());
#         }
 
#         private void TryToGetLeftFork()
#         {
#             Monitor.TryEnter(LeftFork, ref IsCurrentlyHoldingLeftFork);
#         }
 
#         private void TryToGetRightFork()
#         {
#             Monitor.TryEnter(RightFork, ref IsCurrentlyHoldingRightFork);
#         }
 
#         private void DropForks()
#         {
#             DropLeftFork();
#             DropRightFork();
#         }
 
#         private void DropLeftFork()
#         {
#             if (IsCurrentlyHoldingLeftFork)
#             {
#                 IsCurrentlyHoldingLeftFork = false;
#                 Monitor.Exit(LeftFork);
#             }
#         }
 
#         private void DropRightFork()
#         {
#             if (IsCurrentlyHoldingRightFork)
#             {
#                 IsCurrentlyHoldingRightFork = false;
#                 Monitor.Exit(RightFork);
#             }
#         }
 
#         private void Eat()
#         {
#             State = DinerState.Eating;
#             WaitForAMoment();
#         }
 
#         private void Ponder()
#         {
#             State = DinerState.Pondering;
#             WaitForAMoment();
#         }
 
#         private static void WaitForAMoment()
#         {
#             Thread.Sleep(Randomizer.Next(MaximumWaitTime));
#         }
 
#         public void Dispose()
#         {
#             ShouldStopEating = true;
#         }
 
#         public enum DinerState
#         {
#             Eating,
#             TryingToGetForks,
#             Pondering
#         }
#     }
 
#     class Fork { }
# }
 
 
class Philosopher(threading.Thread):
 
    running = True
 
    def __init__(self, xname, forkOnLeft, forkOnRight):
        threading.Thread.__init__(self)
        self.name = xname
        self.forkOnLeft = forkOnLeft
        self.forkOnRight = forkOnRight
 
    def run(self):
        while(self.running):
            #  Philosopher is thinking (but really is sleeping).
            time.sleep( random.uniform(3,13))
            print '%s is hungry and wants to eat food.' % self.name
            self.dine()
 


    def dine(self):
        fork1, fork2 = self.forkOnLeft, self.forkOnRight
 
        while self.running:
            fork1.acquire(True)
            locked = fork2.acquire(False)
            if locked: break
            fork1.release()
            print '%s forks have been swapped' % self.name
            fork1, fork2 = fork2, fork1
        else:
            return
 
        self.dining()
        fork2.release()
        fork1.release()
 
    def dining(self):           
        print '%s has started eating '% self.name
        time.sleep(random.uniform(1,10))
        print '%s has finished eating and left to think.' % self.name
 
    def eatphil():
        forks = [threading.Lock() for n in range(5)]
        philosopherNames = ('Ashish','Mukarram','Ram','Shyam', 'David')
     
        philosophers= [Philosopher(philosopherNames[i], forks[i%5], forks[(i+1)%5]) \
                for i in range(5)]
     
        random.seed(507129) 
        Philosopher.running = True
        for p in philosophers: p.start()
        time.sleep(100)
        Philosopher.running = False
        print ("It has finished now")
 
eatphil()