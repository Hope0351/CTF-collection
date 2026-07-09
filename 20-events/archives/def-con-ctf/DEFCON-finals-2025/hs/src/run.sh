#!/bin/bash
set -u

echo Running level $LEVEL
python -m streamlit run run.py --server.port 5000
