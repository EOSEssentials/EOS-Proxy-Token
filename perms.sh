#!/bin/bash

ACCOUNT=${1:-proxytoken}
PKEY=${2:-EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV}

cleos set account permission $ACCOUNT active \
'{"threshold": 1,"keys": [{"key": "'$PKEY'","weight": 1}],"accounts": [{"permission":{"actor":"'$ACCOUNT'","permission":"eosio.code"},"weight":1}]}' owner
