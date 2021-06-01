# Test Plan and Test Output

## Testing Observations

• At first entry point sanitizer is dispensed and LCD shows instruction to go to second entry point.

• At second entry point body temperature is measured and shown on LCD screen.

• If the body temperature is high buzzer is activated and alert is shown to person on LCD.

• If the person doesn’t sanitize himself and moves directly to enter 2, in this condition also buzzer is activated and alert is shown to person on LCD to sanitize himself.

• Also, image of person is captured when buzzer activates and sent through SMS/email.

• If the maximum allowed limit has reached and someone tries to enter, the buzzer beeps for 2 seconds and LCD shows warning that entry is not allowed as limit has reached however the sanitization system still works to sanitize the person.


## Delay Analysis

|   Condition   |      Time     |
| ------------- | ------------- |
| Pump Operation time  | 250 ms  |
| Temperature Reading time  | 500 ms  |
| Exit condition for IR sensor | 2 * 100 ms |
| Program Execution time | 0.49 ms |
| Total Delay time | 950.49 ms |
