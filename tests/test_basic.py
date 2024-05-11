from os import EX_OK
from subprocess import run
from pytest import mark

EX_MEM_LEAK = 2
VALID_FILES = [
    "tests/xml/test_ping_scan.xml",
]
INVALID_FILES = [
    "tests/xml/test_broken_xml.xml",
    "tests/xml/test_html_input.xml",
    "tests/xml/test_non_nmap.xml",
]


@mark.parametrize("xml_path", VALID_FILES)
def test_valid(xml_path: str, capfd) -> None:
    process = run(["build/elo", xml_path])
    assert process.returncode == EX_OK

    cap = capfd.readouterr()
    print()
    print(cap.out)
    print(cap.err)


@mark.parametrize("xml_path", VALID_FILES)
def test_valid_memory(xml_path: str, capfd) -> None:
    command = [
        "valgrind",
        f"--error-exitcode={EX_MEM_LEAK}",
        "--leak-check=full",
        "build/elo",
        xml_path,
    ]
    process = run(command)
    assert process.returncode != EX_MEM_LEAK

    cap = capfd.readouterr()
    print()
    print(cap.out)
    print(cap.err)


@mark.parametrize("xml_path", INVALID_FILES)
def test_invalid_memory(xml_path: str, capfd) -> None:
    command = [
        "valgrind",
        f"--error-exitcode={EX_MEM_LEAK}",
        "--leak-check=full",
        "build/elo",
        xml_path,
    ]
    process = run(command)
    assert process.returncode != EX_MEM_LEAK

    cap = capfd.readouterr()
    print()
    print(cap.out)
    print(cap.err)
