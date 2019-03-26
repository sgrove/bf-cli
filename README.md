# packageinfo-cli


[![CircleCI](https://circleci.com/gh/yourgithubhandle/packageinfo-cli/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/packageinfo-cli/tree/master)


**Contains the following libraries and executables:**

```
packageinfo-cli@0.0.0
│
├─test/
│   name:    TestPackageinfoCli.exe
│   main:    TestPackageinfoCli
│   require: packageinfo-cli.lib
│
├─library/
│   library name: packageinfo-cli.lib
│   namespace:    PackageinfoCli
│   require:
│
└─executable/
    name:    PackageinfoCliApp.exe
    main:    PackageinfoCliApp
    require: packageinfo-cli.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x PackageinfoCliApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
