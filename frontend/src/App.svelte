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