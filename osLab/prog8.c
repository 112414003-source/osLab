#include <stdio.h>
struct Process {
 int id;
 int arrival_time;
 int burst_time;
 int completion_time;
 int turnaround_time;
 int waiting_time;
};
int main() {
 int n;
 float total_wt = 0, total_tat = 0;
 printf("Enter number of processes: ");
 if (scanf("%d", &n) != 1 || n <= 0) {
 printf("Invalid number of processes.\n");
 return 1;
 }
 struct Process p[n];
 // Read user inputs
 for (int i = 0; i < n; i++) {
 p[i].id = i + 1;
 printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
 scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
 }
 // Sort processes based on Arrival Time (Bubble Sort)
 for (int i = 0; i < n - 1; i++) {
 for (int j = 0; j < n - i - 1; j++) {
 if (p[j].arrival_time > p[j + 1].arrival_time) {
 struct Process temp = p[j];
 p[j] = p[j + 1];
 p[j + 1] = temp;
 }
 }
 }
 // FCFS Scheduling Calculations
 int current_time = 0;
 for (int i = 0; i < n; i++) {
 // If CPU is idle waiting for the next process to arrive
 if (current_time < p[i].arrival_time) {
 current_time = p[i].arrival_time;
 }
 
 p[i].completion_time = current_time + p[i].burst_time;
 p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
 p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
 current_time = p[i].completion_time;
 total_wt += p[i].waiting_time;
 total_tat += p[i].turnaround_time;
 }
 // Print Results Matrix
 printf("\n%-10s %-10s %-10s %-12s %-12s %-10s\n",
 "Process", "Arrival", "Burst", "Completion", "Turnaround", "Waiting");
 
 for (int i = 0; i < n; i++) {
 printf("P%-9d %-10d %-10d %-12d %-12d %-10d\n",
 p[i].id, p[i].arrival_time, p[i].burst_time,
 p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
 }
 printf("\nAverage Turnaround Time = %.2f", total_tat / n);
 printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
 return 0;
}