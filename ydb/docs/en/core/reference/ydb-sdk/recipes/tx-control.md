---
title: "Overview of the code recipe for setting up the transaction execution mode in {{ ydb-short-name }}"
description: "In this article, you will learn how to set up the transaction execution mode in different SDKs to execute queries against {{ ydb-short-name }}."
---

# Setting up the transaction execution mode

To run your queries, first you need to specify the [transaction execution mode](../../../concepts/transactions.md#modes) in the {{ ydb-short-name }} SDK.

Below are code examples showing the {{ ydb-short-name }} SDK built-in tools to create an object for the *transaction execution mode*.

{% include [work in progress message](_includes/addition.md) %}

## Serializable {#serializable}

{% list tabs %}

- Go (native)

   ```go
   package main

   import (
     "context"
     "os"

     "github.com/ydb-platform/ydb-go-sdk/v3"
     "github.com/ydb-platform/ydb-go-sdk/v3/table"
   )

   func main() {
     ctx, cancel := context.WithCancel(context.Background())
     defer cancel()
     db, err := ydb.Open(ctx,
       os.Getenv("YDB_CONNECTION_STRING"),
       ydb.WithAccessTokenCredentials(os.Getenv("YDB_TOKEN")),
     )
     if err != nil {
       panic(err)
     }
     defer db.Close(ctx)
     txControl := table.TxControl(
       table.BeginTx(table.WithSerializableReadWrite()),
       table.CommitTx(),
     )
     err := driver.Table().Do(scope.Ctx, func(ctx context.Context, s table.Session) error {
       _, _, err := s.Execute(ctx, txControl, "SELECT 1", nil)
       return err
     })
     if err != nil {
       fmt.Printf("unexpected error: %v", err)
     }
   }
   ```

{% endlist %}

## Online Read-Only {#online-read-only}

{% list tabs %}

- Go (native)

   ```go
   package main

   import (
     "context"
     "os"

     "github.com/ydb-platform/ydb-go-sdk/v3"
     "github.com/ydb-platform/ydb-go-sdk/v3/table"
   )

   func main() {
     ctx, cancel := context.WithCancel(context.Background())
     defer cancel()
     db, err := ydb.Open(ctx,
       os.Getenv("YDB_CONNECTION_STRING"),
       ydb.WithAccessTokenCredentials(os.Getenv("YDB_TOKEN")),
     )
     if err != nil {
       panic(err)
     }
     defer db.Close(ctx)
     txControl := table.TxControl(
       table.BeginTx(table.WithOnlineReadOnly(table.WithInconsistentReads())),
       table.CommitTx(),
     )
     err := driver.Table().Do(scope.Ctx, func(ctx context.Context, s table.Session) error {
       _, _, err := s.Execute(ctx, txControl, "SELECT 1", nil)
       return err
     })
     if err != nil {
       fmt.Printf("unexpected error: %v", err)
     }
   }
   ```

{% endlist %}

## Stale Read-Only {#stale-read-only}

{% list tabs %}

- Go (native)

   ```go
   package main

   import (
     "context"
     "os"

     "github.com/ydb-platform/ydb-go-sdk/v3"
     "github.com/ydb-platform/ydb-go-sdk/v3/table"
   )

   func main() {
     ctx, cancel := context.WithCancel(context.Background())
     defer cancel()
     db, err := ydb.Open(ctx,
       os.Getenv("YDB_CONNECTION_STRING"),
       ydb.WithAccessTokenCredentials(os.Getenv("YDB_TOKEN")),
     )
     if err != nil {
       panic(err)
     }
     defer db.Close(ctx)
     txControl := table.TxControl(
       table.BeginTx(table.WithStaleReadOnly()),
       table.CommitTx(),
     )
     err := driver.Table().Do(scope.Ctx, func(ctx context.Context, s table.Session) error {
       _, _, err := s.Execute(ctx, txControl, "SELECT 1", nil)
       return err
     })
     if err != nil {
       fmt.Printf("unexpected error: %v", err)
     }
   }
   ```

{% endlist %}

## Snapshot Read-Only {#snapshot-read-only}

{% list tabs %}

- Go (native)

   ```go
   package main

   import (
     "context"
     "os"

     "github.com/ydb-platform/ydb-go-sdk/v3"
     "github.com/ydb-platform/ydb-go-sdk/v3/table"
   )

   func main() {
     ctx, cancel := context.WithCancel(context.Background())
     defer cancel()
     db, err := ydb.Open(ctx,
       os.Getenv("YDB_CONNECTION_STRING"),
       ydb.WithAccessTokenCredentials(os.Getenv("YDB_TOKEN")),
     )
     if err != nil {
       panic(err)
     }
     defer db.Close(ctx)
     txControl := table.TxControl(
       table.BeginTx(table.WithSnapshotReadOnly()),
       table.CommitTx(),
     )
     err := driver.Table().Do(scope.Ctx, func(ctx context.Context, s table.Session) error {
       _, _, err := s.Execute(ctx, txControl, "SELECT 1", nil)
       return err
     })
     if err != nil {
       fmt.Printf("unexpected error: %v", err)
     }
   }
   ```

{% endlist %}
