<svelte:head>
    <link rel="dns-prefetch" href="//fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com/" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Raleway:ital,wght@0,100;0,400;0,800;1,800&display=swap"
          rel="stylesheet">
</svelte:head>

<script>
  import Home from './Home.svelte';
  import Link from './Link.svelte';
  import Router from "svelte-spa-router/Router.svelte";

  const routes = {
    '/': Home,
    '*': Link,
  }
</script>

<Router {routes}/>