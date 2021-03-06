<template>
  <div class="calculator">
    <div><input type="input" placeholder="Enter Serial Code" v-model="serial"></div>
    <br>
    <div class="result" v-show="password !== ''">Root Password: <code id="password">{{ password }}</code></div>
    <div class="invalidsn" v-show="password === ''">Invalid S/N or unlisted S/N type.</div>
  </div>
</template>

<script>
import {calculateRootPassword} from '../lib/xqcalc'

export default {
  data: () => ({
    serial: ''
  }),
  computed: {
    password: function () {
      return calculateRootPassword(this.serial)
    }
  }
}
</script>

<style>

</style>
