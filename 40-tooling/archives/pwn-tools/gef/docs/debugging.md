## Debugging

Debugging GEF has a trick, let's see some examples

## Debugging with pdb

Open gef.py

Search for **class NopCommand(GenericCommand)**, go to do_invoke method and insert:

```python
import pdb; pdb.set_trace()
```

Open a gdb session -> start -> nop

Done!

```bash
gef➤  nop
> /home/dreg/.gef-7c170cf6be3d84b2672a22e43b9128a23fe53c3b.py(6075)do_invoke()
-> args : argparse.Namespace = kwargs["arguments"]
(Pdb) ll
6070 	    @only_if_gdb_running
6071 	    @parse_arguments({"address": "$pc"}, {"--i": 1, "--b": True, "--f": True, "--n": True})
6072 	    def do_invoke(self, _: List[str], **kwargs: Any) -> None:
6073 	        import pdb; pdb.set_trace()
6074
6075 ->	        args : argparse.Namespace = kwargs["arguments"]
6076 	        address = parse_address(args.address)
```

Learn more about [pdb](https://docs.python.org/3/library/pdb.html)

## Debugging with PyCharm

Install [pycharm](https://www.jetbrains.com/help/pycharm/installation-guide.html)

Create a new project:

![pycharm1](../../../../../40-tooling/archives/pwn-tools/gef)

![pycharm2](../../../../../40-tooling/archives/pwn-tools/gef)

Go to menu -> Run -> Edit configurations...:

![pycharm3](../../../../../40-tooling/archives/pwn-tools/gef)

Create a Python Debug Server:

![pycharm4](../../../../../40-tooling/archives/pwn-tools/gef)

![pycharm5](../../../../../40-tooling/archives/pwn-tools/gef)

Debug your new Unnamed:

![pycharm6](../../../../../40-tooling/archives/pwn-tools/gef)

![pycharm7](../../../../../40-tooling/archives/pwn-tools/gef)

Copy the info from output Window to gef.py:

![pycharm8](../../../../../40-tooling/archives/pwn-tools/gef)

First, add to gef.py:

```python
import pydevd_pycharm
```

Second, search for **class NopCommand(GenericCommand)**, go to do_invoke method and insert:

```python
pydevd_pycharm.settrace('localhost', port=35747, stdoutToServer=True, stderrToServer=True)
```

Open a gdb session -> start -> nop

Done!

![pycharm9](../../../../../40-tooling/archives/pwn-tools/gef)


## Debugging with VSCode

The approach to debug GEF with VSCode is relatively similar to that of PyCharm. Make sure to
install the [Python extension for
VSCode](https://marketplace.visualstudio.com/items?itemName=ms-python.python). This will install
`debugpy`, a remote debugger that you can connect to from VSCode and debug anything in GEF from
your session (breakpoints, watchpoints, etc.). Debugging a Python app from VSCode is [extensively
 covered in the official docs](https://code.visualstudio.com/docs/python/debugging) to refer to
 them if you're not sure how it works.

To start a debugging session in GEF, manually run the following Python commands

```python
gef> pi import debugpy; debugpy.listen(5678); pi debugpy.wait_for_client()
```

Alternatively a convenience script named `vscode_debug.py` can also be found in the `scripts`
folder, which you can invoke easily simply using the GDB `source` command:

```text
gef> source /path/to/gef/scripts/vscode_debug.py
```

GEF will be suspended, waiting for a client to connect to the debugger to resume the execution.
Then from your VSCode, edit or create `/path/to/gef/.vscode/launch.json`, and add a debug
configuration to attach to GEF, by specifying the IP address and port (on `localhost` in the
example below, but the remote server can be anywhere):

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: Attach to GEF",
            "type": "python",
            "request": "attach",
            "connect": {
                "host": "localhost",
                "port": 5678
            }
        }
    ]
}
```

Everything is ready to attach to GEF. By default, you can simply hit F5 on VSCode (Start Debugging)

![vscode-dbg](https://user-images.githubusercontent.com/590234/260521923-b730e2b1-8a17-423d-914c-2be0a1abfed4.png)
