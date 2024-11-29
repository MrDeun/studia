#!/bin/bash

rm graphs/*
python src/graphs.py
mv *.png ./graphs/
