<script>
  import {fade, fly} from 'svelte/transition'

  export let copyValue;
  export let size = 50;
  let inputElement;

  let hidden = true;

  function copy() {
    inputElement.select();
    document.execCommand("copy");
    hidden = false;
    setTimeout(() => hidden = true, 1000)
  }
</script>

<input bind:this={inputElement} value={copyValue}>
<div class="component" style="width: {size}px; height: {size}px">
  {#if !hidden}
    <div in:fade={{duration: 200}} out:fly={{y: -10, duration: 700}} class="label">
      <p>Copied!</p>
    </div>
  {/if}
  <button on:click={copy}>
    <img src="copy.svg" alt="Copy">
  </button>
</div>

<style>
  .component {
    position: relative;
  }

  .label {
    position: absolute;
    background: white;
    border-radius: 30px;
    left: -17px;
    top: 5px;
    /*margin: 0 auto;*/
    box-shadow: 0 2px 5px 1px rgba(100, 100, 100, 0.4);
  }

  p {
    padding: 10px;
    margin: 0;
  }

  button {
    width: 100%;
    height: 100%;
    background: transparent;
    border: transparent;
    border-radius: 2em;
    padding: 7px;
  }
  button:hover {
    cursor: pointer;
  }

  img {
    width: 100%;
  }

  input {
    position: absolute;
    opacity: 0;
    top: -50px;
  }
</style>