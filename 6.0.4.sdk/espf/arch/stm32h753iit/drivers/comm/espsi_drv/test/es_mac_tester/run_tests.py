import subprocess
import random
import time

COM_DEV=6
MAC_ADDR=34
# Time to execute in seconds
TEST_TIME = 600

# Name of the test case, number for the ES_SAT_MACGW_CMD command and short description
test_cases = [
    ('TC3', 3),
    ('TC4', 4),
    ('TC6', 6),
    ('TC7', 7),
    ('TC8', 8),
    ('TC9', 9),
    ('TC10', 10),
    ('TC11', 11),
    ('TC12', 12),
    ('TC13', 13),
    ('TC14', 14),
    ('TC16', 16),
    ('TC17', 17),
]

# Test results
test_results = dict()
for tc in test_cases:
    # test counter and error counter
    test_results[tc[0]] = [0,0]

# Log File
with open('test_output.log', 'w') as log_file:

    start_time = time.perf_counter()
    delta_time = 0
    while delta_time < TEST_TIME:
        # Choose a random test from the list
        test_case = random.choice(test_cases)

        # Run the command
        command = f'ES_SAT_MACGW_CMD TC={test_case[1]} COM_PORT={COM_DEV} DEST_MAC_ADDR={MAC_ADDR}'
        log_file.write(f'==> {test_case[0]} - command {command}\n')
        test_return = subprocess.run(command, capture_output=True, text=True)

        log_file.write(test_return.stdout)
        log_file.write(test_return.stderr)

        # Keep track of the results
        test_results[test_case[0]][0] += 1
        if test_return.returncode != 0:
            test_results[test_case[0]][1] += 1
        log_file.write(f'==> {test_case[0]} - return {test_return.returncode}\n')

        # Count the elapsed time
        delta_time = time.perf_counter() - start_time

    # Print out results
    print(f'Elapsed time: {delta_time:.2f} s')
    log_file.write(f'Elapsed time: {delta_time:.2f} s\n')
    for tc in test_results:
        print(f'{tc}: {test_results[tc][1]}/{test_results[tc][0]} errors')
        log_file.write(f'{tc}: {test_results[tc][1]}/{test_results[tc][0]} errors\n')

# Clear the log_file from blank spaces
clean_log = open('test_output_clean.log', 'w')
with open('test_output.log', 'r') as log_file:
    for line in log_file:
        if line.strip() == '':
            pass
        else:
            clean_log.writelines(line)
clean_log.close()
