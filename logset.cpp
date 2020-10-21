#include "logset.h"


LogSet::LogSet() {
    levelset = 0;
    printset = 0;
    filesizeset = 5 * 1024;
}

void LogSet::setPrint(int print) { printset = print; }

void LogSet::setLevel(int level) { levelset = level; }

void LogSet::setFilesize(int size) { filesizeset = size; }

bool LogSet::levelConfig(int n) { return n <= levelset; }

int LogSet::printConfig() { return printset; }

int LogSet::filesizeConfig() { return filesizeset; }