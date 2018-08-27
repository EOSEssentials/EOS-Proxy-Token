# Proxy Token

### You can use this on mainnet!

- `safetransfer`

If you want to be sure the person you're sending tokens to can't lock up your RAM send it through the `safetransfer`
account and add the user you want to send tokens to as the memo. 

Once we are sure this contract is stable the keys to the account will be set to dummy keys. ( making no one able to change it )

**IMPORTANT: Do not interact with dapps through this. If you do they will act as if they are interacting with this contract, 
and not with you.** 


------------



## What this is

Put this contract onto an account with no available RAM and then use it to proxy token transfers from your 
dapp to users that might have code installed.

### The problem

A malicious user can install code on their account which will allow them to insert rows in the name of another
account sending them tokens. This lets them steal RAM by inserting large amounts of garbage into rows when dapps/users 
send them tokens.

### The solution
By sending tokens to a proxy account with no available RAM, and with a memo where the first word of the memo 
is the account you eventually want to send the tokens to, the only account they can assume database row 
permissions for is the proxy, which has no RAM. 


------------------


## Token types
This contract accepts all token types that conform to the basic `eosio.token` contract.
The only method that has to have an identical argument signature is the `transfer` method. 

## Permissions (`eosio.code`)

**You will need to set permissions onto your proxy contract to allow it to send tokens inline.**
You can do this using the `perms.sh` bash script with the following syntax from a cleos enabled machine
**Do not include the `<>`**

`./perms.sh <YOUR_ACCOUNT_NAME> <YOUR_ACCOUNT_PUBLIC_KEY>`

## Using the proxy from your contract

In the same way you are sending transfer to your users you simply change the memo to include the account name
as the first **word** in the memo. **This contract also carries along the rest of the memo after a space**.

Example Memo: `eosio this is a memo`
 
This will send tokens from the proxy to the account `eosio` with the memo `this is a memo`.

You can easily test this on the mainnet by sending tokens to the `tknproxytest` account.
```
cleos transfer YOURACCOUNT tknproxytest "1.0000 EOS" "YOURACCOUNT this is a memo"
``` 

## Alternative options

You can do this from a smart contract without using this intermediate proxy.

Solution relayed from Bart Wyatt by Todd Fleming:

> "Inline transfer to proxy, then inline transfer from proxy. 
Proxy’s active would delegate to contract’s eosio.code
The original contract would issue both transfers, but with a different auth."



## People that helped make this happen
- Todd Fleming
- EOSBet
- Nathan Rempel ( genereos )
- Jesta ( Greymass )
- Igor ( EOS Rio )
- Syed ( EOS Cafe )
- Michael Yeates ( eosDac )
- nsjames ( Scatter )



## Things that *didn't* work.

- There's no way to check an account's `code_hash` from within a smart contract currently.
- There's no way to check an account's `last_code_update` from within a smart contract currently.
- We had an idea for an oracle, we built it out and it worked well and was easy to use from smart 
contracts, however if a malicious actor used a batch transaction to both `setcode` and get tokens from 
a dapp then the oracle solution would fail.




