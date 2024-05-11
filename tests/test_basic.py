from pathlib import Path
from os import EX_OK
from subprocess import run
from pytest import mark

INVALID_FILES = [
    "tests/xml/test_broken_xml.xml",
    "tests/xml/test_html_input.xml",
    "tests/xml/test_non_nmap.xml",
]


@mark.parametrize("xml_path", INVALID_FILES)
def test_invalid(xml_path: Path, capfd) -> None:
    process = run(["build/elo", xml_path])
    assert process.returncode != EX_OK

    cap = capfd.readouterr()
    print(cap.err)
