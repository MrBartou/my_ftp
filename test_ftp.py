#!/usr/bin/env python3

from sys import argv
from time import sleep
import string, random

from os import path

# require pwntools
import pwn

sleep_time = 0.01
username = 'Anonymous'
password = ''

if len(argv) != 3:
    print('USAGE: ./test_ftp.py host port')
    exit(1)

host = argv[1]
port = int(argv[2])


def launch_test_cmd(conn, test_name, info, cmd, expected_code):
    conn.sendline(cmd)
    sleep(sleep_time)

    data = conn.recvline()
    sleep(sleep_time)

    if str(expected_code).encode() in data:
        # pwn.log.success(f'{info}: OK ({cmd})')
        pass
    else:
        pwn.log.failure(f'Test KO: {test_name}: {info}')
        pwn.log.info(f'-> {cmd}')
        pwn.log.info(f'<- {data}')
        pwn.log.info(f'expected {expected_code}')
        # exit(1)


def connect():
    conn = pwn.remote(host, port)
    data = conn.recvline().strip()
    if b'220' in data:
        pwn.log.info('Connection: OK')
    else:
        pwn.log.info(b'<- ' + data)
        pwn.log.info('Connection: KO')
        exit(1)
    return conn


def login(conn, test_name):
    launch_test_cmd(conn, test_name, 'user', f'USER {username}', 331)
    launch_test_cmd(conn, test_name, 'pass', f'PASS {password}', 230)


def test_quit(conn, test_name):
    launch_test_cmd(conn, test_name, 'quit', 'QUIT', 221)


def test_case(conn, test_name):
    launch_test_cmd(conn, test_name, 'user', f'uSeR {username}', 331)
    launch_test_cmd(conn, test_name, 'pass', f'PaSs {password}', 230)
    launch_test_cmd(conn, test_name, 'logout', 'quit', 221)


def test_authentication(conn, test_name):
    launch_test_cmd(conn, test_name, 'user', f'USER {username}', 331)
    launch_test_cmd(conn, test_name, 'pass', f'PASS {password}', 230)
    launch_test_cmd(conn, test_name, 'logout', 'QUIT', 221)


def test_authentication2(conn, test_name):
    # launch_test_cmd(conn, test_name, 'noop', 'NOOP', 530)
    launch_test_cmd(conn, test_name, 'user', f'USER {username}', 331)
    # launch_test_cmd(conn, test_name, 'noop', 'NOOP', 530)
    launch_test_cmd(conn, test_name, 'pass', f'PASS {password}', 230)
    # launch_test_cmd(conn, test_name, 'noop', 'NOOP', 200)

    launch_test_cmd(conn, test_name, 'user', f'USER {username}', 331)
    launch_test_cmd(conn, test_name, 'user', f'USER randomuser', 530)
    launch_test_cmd(conn, test_name, 'user', f'USER {username}', 331)
    launch_test_cmd(conn, test_name, 'pass', f'PASS {password}', 230)
    launch_test_cmd(conn, test_name, 'pass', f'PASS {password}', 230)
    launch_test_cmd(conn, test_name, 'logout', 'QUIT', 221)


def test_error_management_authentication(conn, test_name):
    launch_test_cmd(conn, test_name, 'pass', 'PASS', 503)
    launch_test_cmd(conn, test_name, 'pass', 'USER', 331)
    launch_test_cmd(conn, test_name, 'pass', 'PASS', 503)

    launch_test_cmd(conn, test_name, 'pass', 'USER randomuser', 331)
    launch_test_cmd(conn, test_name, 'pass', 'PASS', 530)
    launch_test_cmd(conn, test_name, 'pass', 'PASS', 503)

    launch_test_cmd(conn, test_name, 'pass', 'USER randomuser', 331)
    launch_test_cmd(conn, test_name, 'pass', 'PASS randompass', 530)
    launch_test_cmd(conn, test_name, 'pass', 'PASS randompass', 503)

    launch_test_cmd(conn, test_name, 'logout', 'QUIT', 221)


def test_directory(conn, test_name):
    login(conn, test_name)

    dir_name_1 = ''.join(random.choice(string.ascii_letters) for _ in range(10))
    dir_name_2 = ''.join(random.choice(string.ascii_letters) for _ in range(10))

    launch_test_cmd(conn, test_name, 'mkd', f'MKD {dir_name_1}/{dir_name_2}', 550)
    if path.isdir(f'{dir_name_1}/{dir_name_2}'):
        pwn.log.failure(f'Test KO: expected no dir "{dir_name_1}/{dir_name_2}"')

    launch_test_cmd(conn, test_name, 'mkd', f'MKD {dir_name_1}', 257)
    if not path.isdir(f'{dir_name_1}'):
        pwn.log.failure(f'Test KO: expected dir "{dir_name_1}"')
    launch_test_cmd(conn, test_name, 'mkd', f'MKD {dir_name_1}/{dir_name_2}', 257)
    if not path.isdir(f'{dir_name_1}/{dir_name_2}'):
        pwn.log.failure(f'Test KO: expected dir "{dir_name_1}/{dir_name_2}"')

    launch_test_cmd(conn, test_name, 'mkd', f'MKD {dir_name_1}', 550)
    launch_test_cmd(conn, test_name, 'mkd', f'MKD {dir_name_1}/{dir_name_2}', 550)

    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}', 550)
    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}/{dir_name_2}', 250)
    if path.isdir(f'{dir_name_1}/{dir_name_2}'):
        pwn.log.failure(f'Test KO: expected remove dir but still here "{dir_name_1}/{dir_name_2}"')
    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}/{dir_name_2}', 550)
    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}', 250)
    if path.isdir(f'{dir_name_1}'):
        pwn.log.failure(f'Test KO: expected remove dir but still here "{dir_name_1}"')
    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}', 550)


def test_directory2(conn, test_name):
    login(conn, test_name)
    global sleep_time
    dir_name_1 = ''.join(random.choice(string.ascii_letters) for _ in range(10))
    dir_name_2 = ''.join(random.choice(string.ascii_letters) for _ in range(10))

    launch_test_cmd(conn, test_name, 'mkd', f'MKD ./{dir_name_1}', 257)
    if not path.isdir(f'{dir_name_1}'):
        pwn.log.failure(f'Test KO: expected dir "{dir_name_1}"')
    launch_test_cmd(conn, test_name, 'mkd', f'MKD ./{dir_name_1}/../{dir_name_1}/./{dir_name_2}', 257)
    if not path.isdir(f'{dir_name_1}/{dir_name_2}'):
        pwn.log.failure(f'Test KO: expected dir "{dir_name_1}/{dir_name_2}"')
    launch_test_cmd(conn, test_name, 'mkd', f'MKD ./{dir_name_1}/../{dir_name_1}/./{dir_name_2}', 550)

    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}/{dir_name_2}', 250)
    if path.isdir(f'{dir_name_1}/{dir_name_2}'):
        pwn.log.failure(f'Test KO: expected remove dir but still here "{dir_name_1}/{dir_name_2}"')
    launch_test_cmd(conn, test_name, 'rmd', f'RMD {dir_name_1}', 250)
    if path.isdir(f'{dir_name_1}'):
        pwn.log.failure(f'Test KO: expected remove dir but still here "{dir_name_1}"')


def run_test_suite(test_func, test_name):
    print(f'Test {test_name}')

    pwn.context.log_level = 'error'
    conn = connect()
    pwn.context.log_level = 'info'

    test_func(conn, test_name)

    pwn.context.log_level = 'error'
    conn.close()
    pwn.context.log_level = 'info'
    pwn.log.success(f'{test_name} OK')
    print()


if __name__ == '__main__':
    run_test_suite(test_quit, 'Quit')
    run_test_suite(test_case, 'Case')

    run_test_suite(test_authentication, 'Authentication')
    run_test_suite(test_authentication2, 'Authentication2')
    run_test_suite(test_error_management_authentication,
                   'Error management authentication')

    run_test_suite(test_directory, 'Directory')
    run_test_suite(test_directory2, 'Directory2')
