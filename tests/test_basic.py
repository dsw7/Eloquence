from os import EX_OK
from subprocess import run
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


def test_help() -> None:
    process = run(["build/elo", "--help"])
    assert process.returncode == EX_FAIL


def test_help_shorthand() -> None:
    process = run(["build/elo", "-h"])
    assert process.returncode == EX_FAIL


def test_help_memory() -> None:
    process = run([*VALGRIND_CMD, "--help"])
    assert process.returncode != EX_MEM_LEAK


def test_help_shorthand_memory() -> None:
    process = run([*VALGRIND_CMD, "-h"])
    assert process.returncode != EX_MEM_LEAK


@mark.parametrize("xml_path", VALID_FILES)
def test_valid(xml_path: str) -> None:
    process = run(["build/elo", xml_path])
    assert process.returncode == EX_OK


@mark.parametrize("xml_path", VALID_FILES)
def test_valid_memory(xml_path: str) -> None:
    process = run([*VALGRIND_CMD, xml_path])
    assert process.returncode != EX_MEM_LEAK


@mark.parametrize("xml_path", INVALID_FILES)
def test_invalid_memory(xml_path: str) -> None:
    process = run([*VALGRIND_CMD, xml_path])
    assert process.returncode != EX_MEM_LEAK
