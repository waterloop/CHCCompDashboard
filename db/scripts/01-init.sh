#!/bin/bash
psql -U postgres -a -f /sqlFiles/installtimeseries.sql
psql -U postgres -a -f /sqlFiles/initdb.sql