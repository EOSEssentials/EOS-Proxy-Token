# Proxy Token

Put this contract onto an account with no available RAM and then use it to proxy token transfers from your 
dapp to users that might have code installed.


## Permissions (`eosio.code`)

You will need to set permissions onto your proxy contract to allow it to send tokens inline.
You can do this using the `perms.sh` bash script with the following syntax from a cleos enabled machine

`./perms.sh <YOUR_ACCOUNT_NAME> <YOUR_ACCOUNT_PUBLIC_KEY>`

Do not include the `<>`