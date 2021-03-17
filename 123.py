"""
blockswap.py

This file tests a binary implementation for blockswap with a naive Python
implementation. To use this, make sure that ./blockswap exists as a binary
implementation for blockswap.
In the output directory, files will be left over if the output differs from the
expected python output. These files are {test_num}.binary.out,
{test_num}.binary.out, {test_num}.in, and {test_num}.diff, where you can see the
inputs, outputs, and differences.
Modify the constants below to adjust the parameters for random testing. You may
also use CTRL-C to end the tests early and get a summary of the testing results.
"""
import difflib
import random
import os
import statistics
import subprocess
import time

# N_LIMIT is the maximum value for n, inclusive.
N_LIMIT = 100_000

# M_LIMIT is the maximum value for m, inclusive.
M_LIMIT = 1_000_000

# TEST_TIMEOUT is the time to run your program in seconds
TEST_TIMEOUT = 3

# TEST_LIMIT is the number of test cases to run. Set to -1 for infinite tests.
TEST_LIMIT = -1

# Reference binary path
REFERENCE_BINARY = './ref-blockswap'

# Test program
TEST_BINARY = './blockswap'

def solve(test_num, input_str):
  start_time = time.perf_counter()
  try:
    process = subprocess.run([REFERENCE_BINARY], input=input_str, encoding='ascii',
      stdout=subprocess.PIPE, timeout=TEST_TIMEOUT)
  except subprocess.TimeoutExpired:
    f = open(f'./outputs/{test_num}.ref.out', 'w')
    f.write("TIMEOUT")
    f.close()
    return False
  final_time = time.perf_counter()

  f = open(f'./outputs/{test_num}.ref.out', 'w')
  f.write(process.stdout)
  f.close()
  return final_time - start_time


def solve_bin(test_num, input_str):
  f = open(f'./outputs/{test_num}.in', 'w')
  f.write(input_str)
  f.close()

  start_time = time.perf_counter()
  try:
    process = subprocess.run([TEST_BINARY], input=input_str, encoding='ascii',
      stdout=subprocess.PIPE, timeout=TEST_TIMEOUT)
  except subprocess.TimeoutExpired:
    f = open(f'./outputs/{test_num}.binary.out', 'w')
    f.write("TIMEOUT")
    f.close()
    return False
  final_time = time.perf_counter()

  f = open(f'./outputs/{test_num}.binary.out', 'w')
  f.write(process.stdout)
  f.close()
  return final_time - start_time

def compare_output(test_num):
  bin_path = f'./outputs/{test_num}.binary.out'
  reference_path = f'./outputs/{test_num}.ref.out'
  in_path = f'./outputs/{test_num}.in'
  bin_file = open(bin_path)
  python_file = open(reference_path)
  diff = list(difflib.unified_diff(bin_file.read(), python_file.read(),
    fromfile='binary', tofile='reference'))
  bin_file.close()
  python_file.close()
  if diff:
    diff_file = open(f'./outputs/{test_num}.diff', 'w')
    diff_file.write("".join(diff))
    diff_file.close()
  else:
    os.remove(bin_path)
    os.remove(reference_path)
    os.remove(in_path)

  return not diff


def main():
  test_num = 1
  successful = 0
  total_tests = TEST_LIMIT
  timings = []

  os.makedirs('./outputs', exist_ok=True)
  try:
    while test_num <= total_tests or total_tests == -1:
      print("=" * 50)
      n = random.randint(1, N_LIMIT)
      m = random.randint(1, M_LIMIT)
      print(f"Test {test_num} (n = {n:n}, m = {m:n})")
      ms = (random.randrange(0, n) for _ in range(m))
      input_str = f"{n} {m}\n" + "\n".join(map(str, ms))

      print("Solving with binary...", end="", flush=True)
      runtime = solve_bin(test_num, input_str)
      timings.append(runtime)
      print(f"✅ ({runtime:0.4f}s)" if runtime else "❌")

      print("Solving with reference solution...", end="", flush=True)
      runtime = solve(test_num, input_str)
      print(f"✅ ({runtime:0.4f}s)" if runtime else "❌")

      print("Comparing output...", end="", flush=True)
      if compare_output(test_num):
        print("✅")
        successful += 1
      else:
        print("❌")
      test_num += 1
      print("=" * 50)
  except KeyboardInterrupt:
    print("")

  print(f"\nPassed {successful}/{test_num - 1}")
  if successful > 0:
    print(f"Timing:", end=" ")
    print(f"{min(timings):0.2f}/{statistics.mean(timings):0.2f}/", end="")
    print(f"/{max(timings):0.2f}/{statistics.stdev(timings):0.2f}", end=" ")
    print("min/avg/max/dev")


if __name__ == "__main__":
  main()