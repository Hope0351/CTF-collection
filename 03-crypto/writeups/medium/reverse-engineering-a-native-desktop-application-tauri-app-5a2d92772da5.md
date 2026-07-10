# :locked_with_key: Reverse Engineering A Native Desktop Application Tauri App 5A2D92772Da5

> **Original Source:** [Reverse Engineering A Native Desktop Application Tauri App 5A2D92772Da5](https://infosecwriteups.com/reverse-engineering-a-native-desktop-application-tauri-app-5a2d92772da5)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

## “From Dev to Rev” Perspectives


The backend binding of Tauri is using a Rust language. The bundled application itself always has a core process and it serves an OEP (Original Entry Point) or a `_start` of the user/developer’s app. Interesting fact to be stated is that this native app doesn’t require Chromium so that it has to render the designated app, yet it takes an advantage from a WebView Libraries which derived from [WRY](https://docs.rs/wry/latest/wry/#:~:text=Wry%20is%20a%20Cross%2Dplatform,re%2Dexports%20APIs%20from%20tao.). This means that all the HTML,CSS and JS later will be loaded in a WebView, just like how Android uses WebView to load a web-based content since it contains a browser engine.


In order to build the basic app for the first time, Tauri needs to know the user/developer’s JSON-like configuration files and that’s why there’s a thing called [tauri.conf.json](https://tauri.app/v1/api/config/). The general structure looks probably like this, taken from the Tauri Github examples and what we’ll be focusing at is in the build objects since it holds the source code location. What we’re interpreting later is that not only a HTML file that will be loaded to the Tauri context but also some of the files, and suppose there’s also a JS. Thus, the distDir or the devPath might points out to the specific src-tauri directory.


```
{
"$schema": "../../core/config-schema/schema.json",
"build": {
"distDir": ["index.html"],
"devPath": ["index.html"],
"beforeDevCommand": "",
"beforeBuildCommand": ""
},
"package": {
"productName": "The Basic Rookie Dev App",
"version": "0.1.0"
},
"tauri": {
"bundle": {
"active": true,
"targets": "all",
"identifier": "com.tauri.dev",
"icon": [
"../.icons/32x32.png",
"../.icons/128x128.png",
"../.icons/128x128@2x.png",
"../.icons/icon.icns",
"../.icons/icon.ico"
],
"resources": [],
"externalBin": [],
"copyright": "",
"category": "DeveloperTool",
"shortDescription": "",
"longDescription": "",
"deb": {
"depends": []
},
"macOS": {
"frameworks": [],
"exceptionDomain": ""
}
},
"allowlist": {
"all": false
},
"windows": [
{
"title": "Aseng was here~!",
"width": 800,
"height": 600,
"resizable": true,
"fullscreen": false
}
],
"security": {
"csp": "default-src 'self'"
}
}
```


Finally, this JSON configuration file will be loaded and built since from the main.rs of the application will handle and passed it to the context generator and Codegen later as a structure. Below is the sample of main Rust code from the same link [here](https://github.com/tauri-apps/tauri/blob/dev/examples/helloworld/main.rs).


```
#![cfg_attr(
all(not(debug_assertions), target_os = "windows"),
windows_subsystem = "windows"
)]

fn main() {
tauri::Builder::default()
.run(tauri::generate_context!(
"../../examples/helloworld/tauri.conf.json"
))
.expect("error while running tauri application");
}
```


If we take a look at the snippet from [https://github.com/tauri-apps/tauri/blob/dev/core/tauri-codegen/src/context.rs](https://github.com/tauri-apps/tauri/blob/dev/core/tauri-codegen/src/context.rs), our assets will also be handled from this code. Each of our defined asset is carefully parsed from its extension and later on through the array of configuration objects.


```
use tauri_utils::assets::AssetKey;
use tauri_utils::config::{AppUrl, Config, PatternKind, WindowUrl};
use tauri_utils::html::{
inject_nonce_token, parse as parse_html, serialize_node as serialize_html_node,
};

#[cfg(feature = "shell-scope")]
use tauri_utils::config::{ShellAllowedArg, ShellAllowedArgs, ShellAllowlistScope};

use crate::embedded_assets::{AssetOptions, CspHashes, EmbeddedAssets, EmbeddedAssetsError};

/// Necessary data needed by [`context_codegen`] to generate code for a Tauri application context.
pub struct ContextData {
pub dev: bool,
pub config: Config,
pub config_parent: PathBuf,
pub root: TokenStream,
}

fn map_core_assets(
options: &AssetOptions,
target: Target,
) -> impl Fn(&AssetKey, &Path, &mut Vec<u8>, &mut CspHashes) -> Result<(), EmbeddedAssetsError> {
#[cfg(feature = "isolation")]
let pattern = tauri_utils::html::PatternObject::from(&options.pattern);
let csp = options.csp;
let dangerous_disable_asset_csp_modification =
options.dangerous_disable_asset_csp_modification.clone();
move |key, path, input, csp_hashes| {
if path.extension() == Some(OsStr::new("html")) {
#[allow(clippy::collapsible_if)]
if csp {
let mut document = parse_html(String::from_utf8_lossy(input).into_owned());

if target == Target::Linux {
::tauri_utils::html::inject_csp_token(&mut document);
}

inject_nonce_token(&mut document, &dangerous_disable_asset_csp_modification);

if dangerous_disable_asset_csp_modification.can_modify("script-src") {
if let Ok(inline_script_elements) = document.select("script:not(empty)") {
let mut scripts = Vec::new();
for inline_script_el in inline_script_elements {
let script = inline_script_el.as_node().text_contents();
let mut hasher = Sha256::new();
hasher.update(&script);
let hash = hasher.finalize();
scripts.push(format!("'sha256-{}'", base64::encode(hash)));
}
csp_hashes
.inline_scripts
.entry(key.clone().into())
.or_default()
.append(&mut scripts);
}
}

#[cfg(feature = "isolation")]
if dangerous_disable_asset_csp_modification.can_modify("style-src") {
if let tauri_utils::html::PatternObject::Isolation { .. } = &pattern {
// create the csp for the isolation iframe styling now, to make the runtime less complex
let mut hasher = Sha256::new();
hasher.update(tauri_utils::pattern::isolation::IFRAME_STYLE);
let hash = hasher.finalize();
csp_hashes
.styles
.push(format!("'sha256-{}'", base64::encode(hash)));
}
}

*input = serialize_html_node(&document);
}
}
Ok(())
}
}

//.... [SNIP] .......

let app_url = if dev {
&config.build.dev_path
} else {
&config.build.dist_dir
};

let assets = match app_url {
AppUrl::Url(url) => match url {
WindowUrl::External(_) => Default::default(),
WindowUrl::App(path) => {
if path.components().count() == 0 {
panic!(
"The `{}` configuration cannot be empty",
if dev { "devPath" } else { "distDir" }
)
}
let assets_path = config_parent.join(path);
if !assets_path.exists() {
panic!(
"The `{}` configuration is set to `{:?}` but this path doesn't exist",
if dev { "devPath" } else { "distDir" },
path
)
}
EmbeddedAssets::new(assets_path, &options, map_core_assets(&options, target))?
}
_ => unimplemented!(),
},
AppUrl::Files(files) => EmbeddedAssets::new(
files
.iter()
.map(|p| config_parent.join(p))
.collect::<Vec<_>>(),
&options,
map_core_assets(&options, target),
)?,
_ => unimplemented!(),
};

// ..... [SNIP] ......
```


Later on, here comes the questions.

>

We are interested in how Tauri App protects our assets. Are they encrypted? Are they stored in a different format from a transformation process? Are they stored in a Tauri special Cloud Storage? Or are they stored in a plain text thus left unprotected?


After looking at those snippets, we know that there’s a reference to `tauri_utils` that handle our main assets and this is where things are getting interesting. Let’s take a look at the snippet below which was taken from the official Tauri Github at [https://github.com/tauri-apps/tauri/blob/dev/core/tauri-utils/src/assets.rs](https://github.com/tauri-apps/tauri/blob/dev/core/tauri-utils/src/assets.rs)


```
/// Represents a container of file assets that are retrievable during runtime.
pub trait Assets: Send + Sync + 'static {
/// Get the content of the passed [`AssetKey`].
fn get(&self, key: &AssetKey) -> Option<Cow<'_, [u8]>>;

/// Gets the hashes for the CSP tag of the HTML on the given path.
fn csp_hashes(&self, html_path: &AssetKey) -> Box<dyn Iterator<Item = CspHash<'_>> + '_>;
}

/// [`Assets`] implementation that only contains compile-time compressed and embedded assets.
#[derive(Debug)]
pub struct EmbeddedAssets {
assets: phf::Map<&'static str, &'static [u8]>,
// Hashes that must be injected to the CSP of every HTML file.
global_hashes: &'static [CspHash<'static>],
// Hashes that are associated to the CSP of the HTML file identified by the map key (the HTML asset key).
html_hashes: phf::Map<&'static str, &'static [CspHash<'static>]>,
}

impl EmbeddedAssets {
/// Creates a new instance from the given asset map and script hash list.
pub const fn new(
map: phf::Map<&'static str, &'static [u8]>,
global_hashes: &'static [CspHash<'static>],
html_hashes: phf::Map<&'static str, &'static [CspHash<'static>]>,
) -> Self {
Self {
assets: map,
global_hashes,
html_hashes,
}
}
}

impl Assets for EmbeddedAssets {
#[cfg(feature = "compression")]
fn get(&self, key: &AssetKey) -> Option<Cow<'_, [u8]>> {
self
.assets
.get(key.as_ref())
.map(|&(mut asdf)| {
// with the exception of extremely small files, output should usually be
// at least as large as the compressed version.
let mut buf = Vec::with_capacity(asdf.len());
brotli::BrotliDecompress(&mut asdf, &mut buf).map(|()| buf)
})
.and_then(Result::ok)
.map(Cow::Owned)
}

#[cfg(not(feature = "compression"))]
fn get(&self, key: &AssetKey) -> Option<Cow<'_, [u8]>> {
self
.assets
.get(key.as_ref())
.copied()
.map(|a| Cow::Owned(a.to_vec()))
}
```


What’s your first thoughts when reading those snippet? Although specific assets are “marked” with some hashes validation, randomized ID and stuff, our assets are not encrypted, yet our assets are only compressed using [Brotli](https://github.com/google/brotli), a lossless data compressor system. According to the reference from this official Taori docs -> [https://tauri.app/v1/guides/building/app-size/](https://tauri.app/v1/guides/building/app-size/), we need to pay attention on this part:


*Tauri Asset Compression Features*


It turns out Brotli Compression is actually enabled by default, but somehow user also have a capability to disable this feature as they like since this is considered as a preferential options. Another things that we need to take note is stated from the security docs itself ([https://tauri.app/v1/references/architecture/security/](https://tauri.app/v1/references/architecture/security/)).


There are some CSP Injection as a initial setup and handling from the context generator and Codegen, and the last point makes the challenge to become harder since we can’t decompile the native desktop apps binary easily.


Some quick notes about the ASAR file reference that is stated from the docs actually just a simple tar-archive file format and the unpacker is already existed, refers to this [answer](https://stackoverflow.com/questions/38523617/how-to-unpack-an-asar-file). ASAR file itself can also be retrieved from static analysis, even using a famous file carver tool which used for a forensic purpose such as [binwalk](https://www.kali.org/tools/binwalk/), yet in Tauri App case, it doesn’t work that easily since all of the assets are entirely loaded in runtime. This means the compression and the decompression mechanism also will be done at runtime. What could be our finale solution for this problem? Since the assets handling is done at runtime, we’ll debug the application at runtime as well so we’ll be using a combination of static and dynamic analysis.

---

*Originally published on [Medium](https://infosecwriteups.com/reverse-engineering-a-native-desktop-application-tauri-app-5a2d92772da5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
