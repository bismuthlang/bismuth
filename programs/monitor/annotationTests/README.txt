How to run tests:
./tester programs/monitor/demo


Tests following "Linear Temporal Logic and Linear Dynamic Logic on Finite Traces" - Giuseppe De Giacomo & Moshe Y. Vardi
1: Safety - "Safety”: []ϕ means that always till the end of the trace ϕ holds.
2: Liveness - “Liveness”: <>ϕ means that eventually before the end of the trace ϕ holds
3: Response - “Response”: []<>ϕ means that for any point in the trace there is a point later in the trace where ϕ holds. 
4: Persistence - “Persistence”: <>[]ϕ means that there exists a point in the trace such that from then on till the end of the trace ϕ holds.

5: absence of A
6: Q responds to P
7: 'in the next state...'
