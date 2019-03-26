PackageinfoCli.Util.foo();

open Async;

module Startup = {
  open Async;

  open Cohttp;
  open Cohttp_async;

  let query = {|
query npm($package: String!) {
  npm {
    package(name: $package) {
      homepage
      keywords
      description
      keywords
      name
      readme
      readmeFilename
      license {
        type
      }
      maintainers {
        name
      }
      versions {
        version
        dependencies {
          name
          version
        }
      }
      downloads {
        lastMonth {
          count
          perDay {
            day
            count
          }
        }
      }
      time {
        versions {
          date
          version
        }
      }
      bundlephobia {
        gzip
        size
        history {
          gzip
          size
          version
        }
        dependencySizes {
          approximateSize
          name
        }
      }
      repository {
        url
        sourceRepository {
          ... on GitHubRepository {
            name
            url
            homepageUrl
            defaultBranchRef {
              name
            }
            stargazers {
              totalCount
            }
            watchers {
              totalCount
            }
            issues(states: OPEN) {
              totalCount
            }
            forks {
              totalCount
            }
            pullRequests(states: OPEN) {
              totalCount
            }
            primaryLanguage {
              name
              color
            }
          }
        }
      }
    }
  }
}|};

  let start = (_port, _tests, ()) => {
    let queryBody =
      `Assoc([
        ("query", `String(query)),
        ("variables", `Assoc([("package", `String("graphql"))])),
      ])
      |> Yojson.Basic.to_string
      |> Cohttp_async.Body.of_string;

    let body =
      Client.post(
        ~body=queryBody,
        Uri.of_string(
          "https://serve.onegraph.com/dynamic?app_id=0b33e830-7cde-4b90-ad7e-2a39c57c0e11&show_metrics=true",
        ),
      )
      >>= (
        ((_resp, bodyBytes)) => {
          Cohttp_async.Body.to_string(bodyBytes) >>| (body => body);
        }
      );

    body
    >>| (
      body => {
        open Yojson.Basic;
        let json = from_string(body);

        print_endline("Received body\n" ++ (json |> pretty_to_string));
      }
    );
  };
};

let spec =
  Command.Spec.(
    empty
    +> flag(
         ~doc="int Source port to listen on",
         "-l",
         optional_with_default(8082, int),
       )
    +> flag(
         ~doc="run tests",
         "--run-tests",
         optional_with_default(false, bool),
       )
  );

let () =
  Command.async_spec(~summary="Start OneGraph", spec, Startup.start)
  |> Command.run;
