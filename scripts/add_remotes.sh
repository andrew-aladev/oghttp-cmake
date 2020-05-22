#!/bin/bash
set -e

DIR=$(dirname "${BASH_SOURCE[0]}")
cd "$DIR"

git remote add github    "git@github.com:andrew-aladev/oghttp-cmake.git"    || true
git remote add bitbucket "git@bitbucket.org:andrew-aladev/oghttp-cmake.git" || true
git remote add gitlab    "git@gitlab.com:andrew-aladev/oghttp-cmake.git"    || true
