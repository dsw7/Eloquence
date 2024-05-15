from os import EX_OK
from subprocess import run
from colorama import Fore, Style
from pytest import mark

EX_FAIL = 1
EX_MEM_LEAK = 2
VALGRIND_CMD = [
    "valgrind",
    f"--error-exitcode={EX_MEM_LEAK}",
    "--leak-check=full",
    "build/elo",
]
VALID_FILES = [
    "tests/xml/test_ping_scan.xml",
]
INVALID_FILES = [
    "tests/xml/test_broken_xml.xml",
    "tests/xml/test_html_input.xml",
    "tests/xml/test_non_nmap.xml",
]
PREFIX_STDOUT = Fore.GREEN + "stdout >>> " + Style.RESET_ALL
PREFIX_STDERR = Fore.RED + "stderr >>> " + Style.RESET_ALL


def print_stdout(raw_stdout: str) -> None:
    if not raw_stdout:
        return

    for line in raw_stdout.split("\n"):
        print(PREFIX_STDOUT + line)


def print_stderr(raw_stderr: str) -> None:
    if not raw_stderr:
        return

    for line in raw_stderr.split("\n"):
        print(PREFIX_STDERR + line)


def test_help(capfd) -> None:
    process = run(["build/elo", "--help"])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode == EX_FAIL


def test_help_shorthand(capfd) -> None:
    process = run(["build/elo", "-h"])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode == EX_FAIL


def test_help_memory(capfd) -> None:
    process = run([*VALGRIND_CMD, "--help"])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode != EX_MEM_LEAK


def test_help_shorthand_memory(capfd) -> None:
    process = run([*VALGRIND_CMD, "-h"])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode != EX_MEM_LEAK


@mark.parametrize("xml_path", VALID_FILES)
def test_valid(xml_path: str, capfd) -> None:
    process = run(["build/elo", xml_path])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode == EX_OK


@mark.parametrize("xml_path", VALID_FILES)
def test_valid_memory(xml_path: str, capfd) -> None:
    process = run([*VALGRIND_CMD, xml_path])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode != EX_MEM_LEAK


@mark.parametrize("xml_path", INVALID_FILES)
def test_invalid_memory(xml_path: str, capfd) -> None:
    process = run([*VALGRIND_CMD, xml_path])

    output = capfd.readouterr()
    print()
    print_stdout(output.out)
    print_stderr(output.err)

    assert process.returncode != EX_MEM_LEAK
